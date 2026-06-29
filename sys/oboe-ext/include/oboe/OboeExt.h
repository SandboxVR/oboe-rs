#ifndef OBOE_EXT_H
#define OBOE_EXT_H

#include "oboe/Oboe.h"

namespace oboe {
  typedef std::shared_ptr<AudioStream> AudioStreamShared;

  typedef void (*DropContextHandler)(void *context);

  typedef DataCallbackResult (*AudioReadyHandler)(void *context,
                                                  AudioStream *oboeStream,
                                                  void *audioData,
                                                  int32_t numFrames);

  typedef void (*ErrorCloseHandler)(void *context,
                                    AudioStream *oboeStream,
                                    Result error);

  class AudioStreamCallbackWrapper
      : public AudioStreamDataCallback, public AudioStreamErrorCallback {
  public:
    AudioStreamCallbackWrapper(void *context,
                               const DropContextHandler drop_context,
                               const AudioReadyHandler audio_ready,
                               const ErrorCloseHandler before_close,
                               const ErrorCloseHandler after_close);

    ~AudioStreamCallbackWrapper();

    DataCallbackResult onAudioReady(AudioStream *oboeStream,
                                    void *audioData,
                                    int32_t numFrames);

    void onErrorBeforeClose(AudioStream *oboeStream,
                            Result error);

    void onErrorAfterClose(AudioStream *oboeStream,
                           Result error);

  private:
    void *_context;
    const DropContextHandler _drop_context;
    const AudioReadyHandler _audio_ready;
    const ErrorCloseHandler _before_close;
    const ErrorCloseHandler _after_close;
  };

  void AudioStreamBuilder_create(AudioStreamBuilder *builder);
  void AudioStreamBuilder_delete(AudioStreamBuilder *builder);
  void AudioStreamBuilder_setCallback(AudioStreamBuilder *builder,
                                      void *context,
                                      const DropContextHandler drop_context,
                                      const AudioReadyHandler audio_ready,
                                      const ErrorCloseHandler before_close,
                                      const ErrorCloseHandler after_close);

  AudioApi AudioStreamBuilder_getAudioApi(const AudioStreamBuilder *builder);
  void AudioStreamBuilder_setAudioApi(AudioStreamBuilder *builder, AudioApi api);
  void AudioStreamBuilder_setChannelCount(AudioStreamBuilder *builder, int32_t channelCount);
  void AudioStreamBuilder_setDirection(AudioStreamBuilder *builder, Direction direction);
  void AudioStreamBuilder_setSampleRate(AudioStreamBuilder *builder, int32_t sampleRate);
  void AudioStreamBuilder_setFramesPerCallback(AudioStreamBuilder *builder, int32_t framesPerCallback);
  void AudioStreamBuilder_setFormat(AudioStreamBuilder *builder, AudioFormat format);
  void AudioStreamBuilder_setBufferCapacityInFrames(AudioStreamBuilder *builder, int32_t bufferCapacityInFrames);
  void AudioStreamBuilder_setSharingMode(AudioStreamBuilder *builder, SharingMode sharingMode);
  void AudioStreamBuilder_setPerformanceMode(AudioStreamBuilder *builder, PerformanceMode performanceMode);
  void AudioStreamBuilder_setUsage(AudioStreamBuilder *builder, Usage usage);
  void AudioStreamBuilder_setContentType(AudioStreamBuilder *builder, ContentType contentType);
  void AudioStreamBuilder_setInputPreset(AudioStreamBuilder *builder, InputPreset inputPreset);
  void AudioStreamBuilder_setSessionId(AudioStreamBuilder *builder, SessionId sessionId);
  void AudioStreamBuilder_setDeviceId(AudioStreamBuilder *builder, int32_t deviceId);
  void AudioStreamBuilder_setChannelConversionAllowed(AudioStreamBuilder *builder, bool allowed);
  void AudioStreamBuilder_setFormatConversionAllowed(AudioStreamBuilder *builder, bool allowed);
  void AudioStreamBuilder_setSampleRateConversionQuality(AudioStreamBuilder *builder, SampleRateConversionQuality quality);
  AudioStreamBase* AudioStreamBuilder_getBase(AudioStreamBuilder *builder);

  int32_t AudioStreamBase_getChannelCount(AudioStreamBase *base);
  Direction AudioStreamBase_getDirection(AudioStreamBase *base);
  int32_t AudioStreamBase_getSampleRate(AudioStreamBase *base);
  int32_t AudioStreamBase_getFramesPerCallback(AudioStreamBase *base);
  AudioFormat AudioStreamBase_getFormat(AudioStreamBase *base);
  int32_t AudioStreamBase_getBufferSizeInFrames(AudioStreamBase *base);
  int32_t AudioStreamBase_getBufferCapacityInFrames(AudioStreamBase *base);
  SharingMode AudioStreamBase_getSharingMode(AudioStreamBase *base);
  PerformanceMode AudioStreamBase_getPerformanceMode(AudioStreamBase *base);
  int32_t AudioStreamBase_getDeviceId(AudioStreamBase *base);
  Usage AudioStreamBase_getUsage(AudioStreamBase *base);
  ContentType AudioStreamBase_getContentType(AudioStreamBase *base);
  InputPreset AudioStreamBase_getInputPreset(AudioStreamBase *base);
  SessionId AudioStreamBase_getSessionId(AudioStreamBase *base);
  bool AudioStreamBase_isChannelConversionAllowed(AudioStreamBase *base);
  bool AudioStreamBase_isFormatConversionAllowed(AudioStreamBase *base);
  SampleRateConversionQuality AudioStreamBase_getSampleRateConversionQuality(AudioStreamBase *base);

  Result AudioStreamBuilder_openStreamShared(AudioStreamBuilder *builder,
                                             AudioStreamShared *sharedStream);

  void AudioStreamShared_clone(const AudioStreamShared *sharedStream,
                               AudioStreamShared *newSharedStream);
  void AudioStreamShared_delete(AudioStreamShared *sharedStream);
  AudioStream *AudioStreamShared_deref(AudioStreamShared *sharedStream);
  Result AudioStream_open(AudioStream *oboeStream);
  Result AudioStream_close(AudioStream *oboeStream);
  Result AudioStream_requestStart(AudioStream *oboeStream);
  Result AudioStream_requestPause(AudioStream *oboeStream);
  Result AudioStream_requestFlush(AudioStream *oboeStream);
  Result AudioStream_requestStop(AudioStream *oboeStream);
  StreamState AudioStream_getState(AudioStream *oboeStream);
  Result AudioStream_waitForStateChange(AudioStream *oboeStream,
                                        StreamState inputState,
                                        StreamState *nextState,
                                        int64_t timeoutNanoseconds);
  ResultWithValue<int32_t>
  AudioStream_setBufferSizeInFrames(AudioStream *oboeStream,
                                    int32_t requestedFrames);
  ResultWithValue<int32_t>
  AudioStream_getXRunCount(AudioStream *oboeStream);
  bool AudioStream_isXRunCountSupported(const AudioStream *oboeStream);
  int32_t AudioStream_getFramesPerBurst(AudioStream *oboeStream);
  ResultWithValue<double>
  AudioStream_calculateLatencyMillis(AudioStream *oboeStream);
  AudioApi AudioStream_getAudioApi(const AudioStream *oboeStream);
  ResultWithValue<int32_t> AudioStream_read(AudioStream *oboeStream,
                                            void* buffer,
                                            int32_t numFrames,
                                            int64_t timeoutNanoseconds);
  ResultWithValue<int32_t> AudioStream_write(AudioStream *oboeStream,
                                             const void* buffer,
                                             int32_t numFrames,
                                             int64_t timeoutNanoseconds);

  AudioStreamBase* AudioStream_getBase(AudioStream *oboeStream);
}

extern "C" {
  void oboe_AudioStreamBuilder_setChannelCount(oboe::AudioStreamBuilder *builder, int32_t channelCount);
  void oboe_AudioStreamBuilder_setDirection(oboe::AudioStreamBuilder *builder, oboe::Direction direction);
  void oboe_AudioStreamBuilder_setSampleRate(oboe::AudioStreamBuilder *builder, int32_t sampleRate);
  void oboe_AudioStreamBuilder_setFramesPerCallback(oboe::AudioStreamBuilder *builder, int32_t framesPerCallback);
  void oboe_AudioStreamBuilder_setFormat(oboe::AudioStreamBuilder *builder, oboe::AudioFormat format);
  void oboe_AudioStreamBuilder_setBufferCapacityInFrames(oboe::AudioStreamBuilder *builder, int32_t bufferCapacityInFrames);
  void oboe_AudioStreamBuilder_setSharingMode(oboe::AudioStreamBuilder *builder, oboe::SharingMode sharingMode);
  void oboe_AudioStreamBuilder_setPerformanceMode(oboe::AudioStreamBuilder *builder, oboe::PerformanceMode performanceMode);
  void oboe_AudioStreamBuilder_setUsage(oboe::AudioStreamBuilder *builder, oboe::Usage usage);
  void oboe_AudioStreamBuilder_setContentType(oboe::AudioStreamBuilder *builder, oboe::ContentType contentType);
  void oboe_AudioStreamBuilder_setInputPreset(oboe::AudioStreamBuilder *builder, oboe::InputPreset inputPreset);
  void oboe_AudioStreamBuilder_setSessionId(oboe::AudioStreamBuilder *builder, oboe::SessionId sessionId);
  void oboe_AudioStreamBuilder_setDeviceId(oboe::AudioStreamBuilder *builder, int32_t deviceId);
  void oboe_AudioStreamBuilder_setChannelConversionAllowed(oboe::AudioStreamBuilder *builder, bool allowed);
  void oboe_AudioStreamBuilder_setFormatConversionAllowed(oboe::AudioStreamBuilder *builder, bool allowed);
  void oboe_AudioStreamBuilder_setSampleRateConversionQuality(oboe::AudioStreamBuilder *builder, oboe::SampleRateConversionQuality quality);

  int32_t oboe_AudioStreamBase_getChannelCount(oboe::AudioStreamBase *base);
  oboe::Direction oboe_AudioStreamBase_getDirection(oboe::AudioStreamBase *base);
  int32_t oboe_AudioStreamBase_getSampleRate(oboe::AudioStreamBase *base);
  int32_t oboe_AudioStreamBase_getFramesPerCallback(oboe::AudioStreamBase *base);
  oboe::AudioFormat oboe_AudioStreamBase_getFormat(oboe::AudioStreamBase *base);
  int32_t oboe_AudioStreamBase_getBufferSizeInFrames(oboe::AudioStreamBase *base);
  int32_t oboe_AudioStreamBase_getBufferCapacityInFrames(oboe::AudioStreamBase *base);
  oboe::SharingMode oboe_AudioStreamBase_getSharingMode(oboe::AudioStreamBase *base);
  oboe::PerformanceMode oboe_AudioStreamBase_getPerformanceMode(oboe::AudioStreamBase *base);
  int32_t oboe_AudioStreamBase_getDeviceId(oboe::AudioStreamBase *base);
  oboe::Usage oboe_AudioStreamBase_getUsage(oboe::AudioStreamBase *base);
  oboe::ContentType oboe_AudioStreamBase_getContentType(oboe::AudioStreamBase *base);
  oboe::InputPreset oboe_AudioStreamBase_getInputPreset(oboe::AudioStreamBase *base);
  oboe::SessionId oboe_AudioStreamBase_getSessionId(oboe::AudioStreamBase *base);
  bool oboe_AudioStreamBase_isChannelConversionAllowed(oboe::AudioStreamBase *base);
  bool oboe_AudioStreamBase_isFormatConversionAllowed(oboe::AudioStreamBase *base);
  oboe::SampleRateConversionQuality oboe_AudioStreamBase_getSampleRateConversionQuality(oboe::AudioStreamBase *base);
}

#endif
