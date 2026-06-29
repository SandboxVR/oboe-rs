#![doc = include_str!("../README.md")]
#![allow(
    non_upper_case_globals,
    non_camel_case_types,
    non_snake_case,
    deref_nullptr, // TODO: Remove after closing https://github.com/rust-lang/rust-bindgen/issues/1651
    clippy::redundant_static_lifetimes, // TODO: Remove after that this issue will be fixed in bindgen
    clippy::missing_safety_doc
)]

#[cfg(all(not(target_os = "android"), not(feature = "test")))]
compile_error!("Currently oboe-sys only supports Android platform");

#[cfg(feature = "generate-bindings")]
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

#[cfg(all(
    not(feature = "generate-bindings"),
    any(target_os = "android", test),
    target_arch = "arm"
))]
include!("bindings_armv7.rs");

#[cfg(all(
    not(feature = "generate-bindings"),
    any(target_os = "android", test),
    target_arch = "aarch64"
))]
include!("bindings_aarch64.rs");

#[cfg(all(
    not(feature = "generate-bindings"),
    any(target_os = "android", test),
    target_arch = "x86"
))]
include!("bindings_i686.rs");

#[cfg(all(
    not(feature = "generate-bindings"),
    any(target_os = "android", test),
    target_arch = "x86_64"
))]
include!("bindings_x86_64.rs");

#[cfg(not(feature = "generate-bindings"))]
extern "C" {
    pub fn oboe_AudioStreamBuilder_setChannelCount(
        builder: *mut oboe_AudioStreamBuilder,
        channel_count: i32,
    );
    pub fn oboe_AudioStreamBuilder_setDirection(
        builder: *mut oboe_AudioStreamBuilder,
        direction: oboe_Direction,
    );
    pub fn oboe_AudioStreamBuilder_setSampleRate(
        builder: *mut oboe_AudioStreamBuilder,
        sample_rate: i32,
    );
    pub fn oboe_AudioStreamBuilder_setFramesPerCallback(
        builder: *mut oboe_AudioStreamBuilder,
        frames_per_callback: i32,
    );
    pub fn oboe_AudioStreamBuilder_setFormat(
        builder: *mut oboe_AudioStreamBuilder,
        format: oboe_AudioFormat,
    );
    pub fn oboe_AudioStreamBuilder_setBufferCapacityInFrames(
        builder: *mut oboe_AudioStreamBuilder,
        buffer_capacity_in_frames: i32,
    );
    pub fn oboe_AudioStreamBuilder_setSharingMode(
        builder: *mut oboe_AudioStreamBuilder,
        sharing_mode: oboe_SharingMode,
    );
    pub fn oboe_AudioStreamBuilder_setPerformanceMode(
        builder: *mut oboe_AudioStreamBuilder,
        performance_mode: oboe_PerformanceMode,
    );
    pub fn oboe_AudioStreamBuilder_setUsage(
        builder: *mut oboe_AudioStreamBuilder,
        usage: oboe_Usage,
    );
    pub fn oboe_AudioStreamBuilder_setContentType(
        builder: *mut oboe_AudioStreamBuilder,
        content_type: oboe_ContentType,
    );
    pub fn oboe_AudioStreamBuilder_setInputPreset(
        builder: *mut oboe_AudioStreamBuilder,
        input_preset: oboe_InputPreset,
    );
    pub fn oboe_AudioStreamBuilder_setSessionId(
        builder: *mut oboe_AudioStreamBuilder,
        session_id: oboe_SessionId,
    );
    pub fn oboe_AudioStreamBuilder_setDeviceId(
        builder: *mut oboe_AudioStreamBuilder,
        device_id: i32,
    );
    pub fn oboe_AudioStreamBuilder_setChannelConversionAllowed(
        builder: *mut oboe_AudioStreamBuilder,
        allowed: bool,
    );
    pub fn oboe_AudioStreamBuilder_setFormatConversionAllowed(
        builder: *mut oboe_AudioStreamBuilder,
        allowed: bool,
    );
    pub fn oboe_AudioStreamBuilder_setSampleRateConversionQuality(
        builder: *mut oboe_AudioStreamBuilder,
        quality: oboe_SampleRateConversionQuality,
    );

    pub fn oboe_AudioStreamBase_getChannelCount(base: *mut oboe_AudioStreamBase) -> i32;
    pub fn oboe_AudioStreamBase_getDirection(base: *mut oboe_AudioStreamBase) -> oboe_Direction;
    pub fn oboe_AudioStreamBase_getSampleRate(base: *mut oboe_AudioStreamBase) -> i32;
    pub fn oboe_AudioStreamBase_getFramesPerCallback(base: *mut oboe_AudioStreamBase) -> i32;
    pub fn oboe_AudioStreamBase_getFormat(base: *mut oboe_AudioStreamBase) -> oboe_AudioFormat;
    pub fn oboe_AudioStreamBase_getBufferSizeInFrames(base: *mut oboe_AudioStreamBase) -> i32;
    pub fn oboe_AudioStreamBase_getBufferCapacityInFrames(base: *mut oboe_AudioStreamBase) -> i32;
    pub fn oboe_AudioStreamBase_getSharingMode(base: *mut oboe_AudioStreamBase)
        -> oboe_SharingMode;
    pub fn oboe_AudioStreamBase_getPerformanceMode(
        base: *mut oboe_AudioStreamBase,
    ) -> oboe_PerformanceMode;
    pub fn oboe_AudioStreamBase_getDeviceId(base: *mut oboe_AudioStreamBase) -> i32;
    pub fn oboe_AudioStreamBase_getUsage(base: *mut oboe_AudioStreamBase) -> oboe_Usage;
    pub fn oboe_AudioStreamBase_getContentType(base: *mut oboe_AudioStreamBase)
        -> oboe_ContentType;
    pub fn oboe_AudioStreamBase_getInputPreset(base: *mut oboe_AudioStreamBase)
        -> oboe_InputPreset;
    pub fn oboe_AudioStreamBase_getSessionId(base: *mut oboe_AudioStreamBase) -> oboe_SessionId;
    pub fn oboe_AudioStreamBase_isChannelConversionAllowed(base: *mut oboe_AudioStreamBase)
        -> bool;
    pub fn oboe_AudioStreamBase_isFormatConversionAllowed(base: *mut oboe_AudioStreamBase) -> bool;
    pub fn oboe_AudioStreamBase_getSampleRateConversionQuality(
        base: *mut oboe_AudioStreamBase,
    ) -> oboe_SampleRateConversionQuality;
}
