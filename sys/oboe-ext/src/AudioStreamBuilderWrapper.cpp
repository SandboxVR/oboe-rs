#include "oboe/OboeExt.h"

namespace oboe {
  /*void AudioStreamBuilder_init(AudioStreamBuilder *builder) {
    new (builder) AudioStreamBuilder();
  }

  void AudioStreamBuilder_drop(AudioStreamBuilder *builder) {
    builder->~AudioStreamBuilder();
  }*/

  void AudioStreamBuilder_create(AudioStreamBuilder *builder) {
    new(builder) AudioStreamBuilder(); // call constructor on preallocated data buffer
  }

  void AudioStreamBuilder_delete(AudioStreamBuilder *builder) {
    builder->~AudioStreamBuilder(); // call destructor directly to avoid free data
  }

  AudioApi AudioStreamBuilder_getAudioApi(const AudioStreamBuilder *builder) {
    return builder->getAudioApi();
  }

  void AudioStreamBuilder_setAudioApi(AudioStreamBuilder *builder, AudioApi api) {
    builder->setAudioApi(api);
  }

  void AudioStreamBuilder_setChannelCount(AudioStreamBuilder *builder, int32_t channelCount) {
    builder->setChannelCount(channelCount);
  }

  void AudioStreamBuilder_setDirection(AudioStreamBuilder *builder, Direction direction) {
    builder->setDirection(direction);
  }

  void AudioStreamBuilder_setSampleRate(AudioStreamBuilder *builder, int32_t sampleRate) {
    builder->setSampleRate(sampleRate);
  }

  void AudioStreamBuilder_setFramesPerCallback(AudioStreamBuilder *builder, int32_t framesPerCallback) {
    builder->setFramesPerCallback(framesPerCallback);
  }

  void AudioStreamBuilder_setFormat(AudioStreamBuilder *builder, AudioFormat format) {
    builder->setFormat(format);
  }

  void AudioStreamBuilder_setBufferCapacityInFrames(AudioStreamBuilder *builder, int32_t bufferCapacityInFrames) {
    builder->setBufferCapacityInFrames(bufferCapacityInFrames);
  }

  void AudioStreamBuilder_setSharingMode(AudioStreamBuilder *builder, SharingMode sharingMode) {
    builder->setSharingMode(sharingMode);
  }

  void AudioStreamBuilder_setPerformanceMode(AudioStreamBuilder *builder, PerformanceMode performanceMode) {
    builder->setPerformanceMode(performanceMode);
  }

  void AudioStreamBuilder_setUsage(AudioStreamBuilder *builder, Usage usage) {
    builder->setUsage(usage);
  }

  void AudioStreamBuilder_setContentType(AudioStreamBuilder *builder, ContentType contentType) {
    builder->setContentType(contentType);
  }

  void AudioStreamBuilder_setInputPreset(AudioStreamBuilder *builder, InputPreset inputPreset) {
    builder->setInputPreset(inputPreset);
  }

  void AudioStreamBuilder_setSessionId(AudioStreamBuilder *builder, SessionId sessionId) {
    builder->setSessionId(sessionId);
  }

  void AudioStreamBuilder_setDeviceId(AudioStreamBuilder *builder, int32_t deviceId) {
    builder->setDeviceId(deviceId);
  }

  void AudioStreamBuilder_setChannelConversionAllowed(AudioStreamBuilder *builder, bool allowed) {
    builder->setChannelConversionAllowed(allowed);
  }

  void AudioStreamBuilder_setFormatConversionAllowed(AudioStreamBuilder *builder, bool allowed) {
    builder->setFormatConversionAllowed(allowed);
  }

  void AudioStreamBuilder_setSampleRateConversionQuality(AudioStreamBuilder *builder, SampleRateConversionQuality quality) {
    builder->setSampleRateConversionQuality(quality);
  }

  int32_t AudioStreamBase_getChannelCount(AudioStreamBase *base) {
    return base->getChannelCount();
  }

  Direction AudioStreamBase_getDirection(AudioStreamBase *base) {
    return base->getDirection();
  }

  int32_t AudioStreamBase_getSampleRate(AudioStreamBase *base) {
    return base->getSampleRate();
  }

  int32_t AudioStreamBase_getFramesPerCallback(AudioStreamBase *base) {
    return base->getFramesPerCallback();
  }

  AudioFormat AudioStreamBase_getFormat(AudioStreamBase *base) {
    return base->getFormat();
  }

  int32_t AudioStreamBase_getBufferSizeInFrames(AudioStreamBase *base) {
    return base->getBufferSizeInFrames();
  }

  int32_t AudioStreamBase_getBufferCapacityInFrames(AudioStreamBase *base) {
    return base->getBufferCapacityInFrames();
  }

  SharingMode AudioStreamBase_getSharingMode(AudioStreamBase *base) {
    return base->getSharingMode();
  }

  PerformanceMode AudioStreamBase_getPerformanceMode(AudioStreamBase *base) {
    return base->getPerformanceMode();
  }

  int32_t AudioStreamBase_getDeviceId(AudioStreamBase *base) {
    return base->getDeviceId();
  }

  Usage AudioStreamBase_getUsage(AudioStreamBase *base) {
    return base->getUsage();
  }

  ContentType AudioStreamBase_getContentType(AudioStreamBase *base) {
    return base->getContentType();
  }

  InputPreset AudioStreamBase_getInputPreset(AudioStreamBase *base) {
    return base->getInputPreset();
  }

  SessionId AudioStreamBase_getSessionId(AudioStreamBase *base) {
    return base->getSessionId();
  }

  bool AudioStreamBase_isChannelConversionAllowed(AudioStreamBase *base) {
    return base->isChannelConversionAllowed();
  }

  bool AudioStreamBase_isFormatConversionAllowed(AudioStreamBase *base) {
    return base->isFormatConversionAllowed();
  }

  SampleRateConversionQuality AudioStreamBase_getSampleRateConversionQuality(AudioStreamBase *base) {
    return base->getSampleRateConversionQuality();
  }

  /// Takes ownership of context (drop_context will be called to free it).
  void AudioStreamBuilder_setCallback(AudioStreamBuilder *builder,
                                      void *context,
                                      const DropContextHandler drop_context,
                                      const AudioReadyHandler audio_ready,
                                      const ErrorCloseHandler before_close,
                                      const ErrorCloseHandler after_close) {
    auto s = std::make_shared<AudioStreamCallbackWrapper>(
        context,
        drop_context,
        audio_ready,
        before_close,
        after_close);

    builder->setDataCallback(s);
    builder->setErrorCallback(s);
  }

  AudioStreamBase* AudioStreamBuilder_getBase(AudioStreamBuilder *builder) {
    return static_cast<AudioStreamBase*>(builder);
  }

  Result AudioStreamBuilder_openStreamShared(AudioStreamBuilder *builder,
                                             AudioStreamShared *sharedStream) {
    new(sharedStream) std::shared_ptr<AudioStream>(); // call constructor on preallocated data buffer
    return builder->openStream(*sharedStream);
  }
}

extern "C" {
  void oboe_AudioStreamBuilder_setChannelCount(oboe::AudioStreamBuilder *builder, int32_t channelCount) {
    oboe::AudioStreamBuilder_setChannelCount(builder, channelCount);
  }

  void oboe_AudioStreamBuilder_setDirection(oboe::AudioStreamBuilder *builder, oboe::Direction direction) {
    oboe::AudioStreamBuilder_setDirection(builder, direction);
  }

  void oboe_AudioStreamBuilder_setSampleRate(oboe::AudioStreamBuilder *builder, int32_t sampleRate) {
    oboe::AudioStreamBuilder_setSampleRate(builder, sampleRate);
  }

  void oboe_AudioStreamBuilder_setFramesPerCallback(oboe::AudioStreamBuilder *builder, int32_t framesPerCallback) {
    oboe::AudioStreamBuilder_setFramesPerCallback(builder, framesPerCallback);
  }

  void oboe_AudioStreamBuilder_setFormat(oboe::AudioStreamBuilder *builder, oboe::AudioFormat format) {
    oboe::AudioStreamBuilder_setFormat(builder, format);
  }

  void oboe_AudioStreamBuilder_setBufferCapacityInFrames(oboe::AudioStreamBuilder *builder, int32_t bufferCapacityInFrames) {
    oboe::AudioStreamBuilder_setBufferCapacityInFrames(builder, bufferCapacityInFrames);
  }

  void oboe_AudioStreamBuilder_setSharingMode(oboe::AudioStreamBuilder *builder, oboe::SharingMode sharingMode) {
    oboe::AudioStreamBuilder_setSharingMode(builder, sharingMode);
  }

  void oboe_AudioStreamBuilder_setPerformanceMode(oboe::AudioStreamBuilder *builder, oboe::PerformanceMode performanceMode) {
    oboe::AudioStreamBuilder_setPerformanceMode(builder, performanceMode);
  }

  void oboe_AudioStreamBuilder_setUsage(oboe::AudioStreamBuilder *builder, oboe::Usage usage) {
    oboe::AudioStreamBuilder_setUsage(builder, usage);
  }

  void oboe_AudioStreamBuilder_setContentType(oboe::AudioStreamBuilder *builder, oboe::ContentType contentType) {
    oboe::AudioStreamBuilder_setContentType(builder, contentType);
  }

  void oboe_AudioStreamBuilder_setInputPreset(oboe::AudioStreamBuilder *builder, oboe::InputPreset inputPreset) {
    oboe::AudioStreamBuilder_setInputPreset(builder, inputPreset);
  }

  void oboe_AudioStreamBuilder_setSessionId(oboe::AudioStreamBuilder *builder, oboe::SessionId sessionId) {
    oboe::AudioStreamBuilder_setSessionId(builder, sessionId);
  }

  void oboe_AudioStreamBuilder_setDeviceId(oboe::AudioStreamBuilder *builder, int32_t deviceId) {
    oboe::AudioStreamBuilder_setDeviceId(builder, deviceId);
  }

  void oboe_AudioStreamBuilder_setChannelConversionAllowed(oboe::AudioStreamBuilder *builder, bool allowed) {
    oboe::AudioStreamBuilder_setChannelConversionAllowed(builder, allowed);
  }

  void oboe_AudioStreamBuilder_setFormatConversionAllowed(oboe::AudioStreamBuilder *builder, bool allowed) {
    oboe::AudioStreamBuilder_setFormatConversionAllowed(builder, allowed);
  }

  void oboe_AudioStreamBuilder_setSampleRateConversionQuality(oboe::AudioStreamBuilder *builder, oboe::SampleRateConversionQuality quality) {
    oboe::AudioStreamBuilder_setSampleRateConversionQuality(builder, quality);
  }

  int32_t oboe_AudioStreamBase_getChannelCount(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getChannelCount(base);
  }

  oboe::Direction oboe_AudioStreamBase_getDirection(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getDirection(base);
  }

  int32_t oboe_AudioStreamBase_getSampleRate(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getSampleRate(base);
  }

  int32_t oboe_AudioStreamBase_getFramesPerCallback(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getFramesPerCallback(base);
  }

  oboe::AudioFormat oboe_AudioStreamBase_getFormat(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getFormat(base);
  }

  int32_t oboe_AudioStreamBase_getBufferSizeInFrames(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getBufferSizeInFrames(base);
  }

  int32_t oboe_AudioStreamBase_getBufferCapacityInFrames(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getBufferCapacityInFrames(base);
  }

  oboe::SharingMode oboe_AudioStreamBase_getSharingMode(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getSharingMode(base);
  }

  oboe::PerformanceMode oboe_AudioStreamBase_getPerformanceMode(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getPerformanceMode(base);
  }

  int32_t oboe_AudioStreamBase_getDeviceId(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getDeviceId(base);
  }

  oboe::Usage oboe_AudioStreamBase_getUsage(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getUsage(base);
  }

  oboe::ContentType oboe_AudioStreamBase_getContentType(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getContentType(base);
  }

  oboe::InputPreset oboe_AudioStreamBase_getInputPreset(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getInputPreset(base);
  }

  oboe::SessionId oboe_AudioStreamBase_getSessionId(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getSessionId(base);
  }

  bool oboe_AudioStreamBase_isChannelConversionAllowed(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_isChannelConversionAllowed(base);
  }

  bool oboe_AudioStreamBase_isFormatConversionAllowed(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_isFormatConversionAllowed(base);
  }

  oboe::SampleRateConversionQuality oboe_AudioStreamBase_getSampleRateConversionQuality(oboe::AudioStreamBase *base) {
    return oboe::AudioStreamBase_getSampleRateConversionQuality(base);
  }
}
