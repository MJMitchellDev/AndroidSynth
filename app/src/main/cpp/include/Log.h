#pragma once



// #ifndef NDEBUG

// #include <android/log.h>
// #define LOGD(args...) \
//     __android_log_print(android_LogPriority::ANDROID_LOG_DEBUG, "WavetableSynthesizer", args)
// #else
    #define LOGD(args, ...)  do {} while(0)
// #endif
