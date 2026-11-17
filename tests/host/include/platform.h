#pragma once
#include <cstdint>
#include <cstdlib>
#include <ctime>
#define FLOWGRAPH_ANDROID_INTERNAL 0
#define FLOWGRAPH_OUTER_NAMESPACE oboe
#define RESAMPLER_OUTER_NAMESPACE oboe
using aaudio_allowed_capture_policy_t = int32_t;
#include <unistd.h>
#include <sched.h>
#define OBOE_NO_INCLUDE_AAUDIO 1
#define __NDK_MAJOR__ 23
#define __ANDROID_API_L__ 21
#define __ANDROID_API_M__ 23
#define __ANDROID_API_N__ 24
#define __ANDROID_API_O__ 26
#define __ANDROID_API_O_MR1__ 27
#define __ANDROID_API_P__ 28
#ifdef __APPLE__
#define TIMER_ABSTIME 1
inline int clock_nanosleep(clockid_t, int, const timespec *, timespec *) { std::abort(); }
inline pid_t gettid() { return getpid(); }
inline int sched_getscheduler(pid_t) { return SCHED_OTHER; }
#endif
#ifndef SCHED_RESET_ON_FORK
#define SCHED_RESET_ON_FORK 0x40000000
#endif
#include "common/QuirksManager.h"
