#ifndef _TARGET_H_
#define _TARGET_H_

#ifdef _WIN32
  #ifdef _WIN64
    #define __WIN64__
  #else
    #define __WIN32__
  #endif
#elif __APPLE__
    #include <TargetConditionals.h>

    #if TARGET_IPHONE_SIMULATOR
      #define __IOS_SIM__
    #elif TARGET_OS_IPHONE
      #define __IOS__
    #elif TARGET_OS_MAC
      #define __OSX__
    #else
      #error "Unknown Apple platform"
    #endif
#elif __ANDROID__
  // Do nothing, we suppor this platform
#elif __linux
    #error "Linux is unsupported"
#elif __unix // all unices not caught above
    #error "General unix is unsupported"
#elif __posix
    #error "Platform unsupported"
#endif

#endif /* _TARGET_H_ */
