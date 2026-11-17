// Exercise production Oboe callbacks with only the Android OS calls stubbed.
// Including the implementation exposes its private stream registry to this test.
#include "aaudio/AudioStreamAAudio.cpp"
#include "common/FilterAudioStream.h"
#include <condition_variable>
#include <future>
#include <iostream>

// Builder backend selection requires Android; it is not used by this test.
bool oboe::OboeGlobals::mWorkaroundsEnabled = true;
bool oboe::AudioStreamBuilder::isAAudioSupported() { std::abort(); }
bool oboe::AudioStreamBuilder::isAAudioRecommended() { std::abort(); }

using namespace oboe;

struct Gate : AudioStreamErrorCallback {
    std::mutex mutex;
    std::condition_variable cv;
    bool entered = false;
    bool resume = false;
    bool afterClose = false;
    void onErrorBeforeClose(AudioStream *, Result) override {
        std::unique_lock<std::mutex> lock(mutex);
        entered = true;
        cv.notify_all();
        cv.wait(lock, [&] { return resume; });
    }
    void onErrorAfterClose(AudioStream *, Result) override { afterClose = true; }
};

struct Child : AudioStreamAAudio {
    using AudioStreamAAudio::AudioStreamAAudio;
    using AudioStreamAAudio::internalErrorCallback;
    void setSelf(std::shared_ptr<AudioStream> self) { setWeakThis(self); }
    std::promise<void> destroyed;
    ~Child() override { destroyed.set_value(); }
};

struct Parent : FilterAudioStream {
    using FilterAudioStream::FilterAudioStream;
    void setSelf(std::shared_ptr<AudioStream> self) { setWeakThis(self); }
};

static bool disableParentRetention = false;

static void run(bool closeFirst) {
    auto gate = std::make_shared<Gate>();
    AudioStreamBuilder builder;
    builder.setErrorCallback(gate);
    auto child = std::make_shared<Child>(builder);
    child->setSelf(child);
    auto parent = std::make_shared<Parent>(builder, child);
    parent->setSelf(parent);
    if (disableParentRetention) child->setParentStream(nullptr);
    auto dead = child->destroyed.get_future();
    std::weak_ptr<AudioStream> weakParent = parent;
    auto *rawChild = child.get();
    AAudioStreamCollection::getInstance().addStream(rawChild);
    child.reset(); // parent and callback worker own the stream, just as in oboe-rs

    if (!closeFirst) {
        Child::internalErrorCallback(nullptr, rawChild, (int) Result::ErrorDisconnected);
        std::unique_lock<std::mutex> lock(gate->mutex);
        if (!gate->cv.wait_for(lock, std::chrono::seconds(5), [&] { return gate->entered; })) {
            std::abort();
        }
    }
    parent->close(); // AudioStreamAsync::drop closes before releasing its shared_ptr
    parent.reset();

    if (!closeFirst) {
        // Before the upstream fix the parent is destroyed here, while the worker
        // still holds its raw callback pointer. Do not proceed into that UAF.
        if (weakParent.expired()) {
            std::cerr << "FilterAudioStream destroyed during error callback\n";
            std::abort();
        }
        {
            std::lock_guard<std::mutex> lock(gate->mutex);
            gate->resume = true;
        }
        gate->cv.notify_all();
    }
    if (dead.wait_for(std::chrono::seconds(5)) != std::future_status::ready) std::abort();
    assert(weakParent.expired());
    assert(gate->afterClose == !closeFirst);

    // Late framework callbacks must be rejected before touching the freed pointer.
    Child::internalErrorCallback(nullptr, rawChild, (int) Result::ErrorDisconnected);
    assert(oboe_aaudio_data_callback_proc(nullptr, rawChild, nullptr, 0)
            == (int) DataCallbackResult::Stop);
}

int main(int argc, char **) {
    disableParentRetention = argc > 1;
    for (int i = 0; i < 1000; ++i) {
        run(false);
        run(true);
    }
    std::cout << "PASS: 1000 callback-first and 1000 close-first teardowns\n";
}
