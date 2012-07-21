#ifndef I3D_OS_IPHONE
#   define I3D_OS_IPHONE 1
#endif
#ifndef I3D_PLATFORM_IPHONE
#   define I3D_PLATFORM_IPHONE 1
#endif
#ifndef IW_ASSERTION_CHANNEL_ADMOB
#   define IW_ASSERTION_CHANNEL_ADMOB 1
#endif
#ifndef IW_MKF_EDK
#   define IW_MKF_EDK 1
#endif
#ifndef IW_MKF_S3EADMOB_BUILD
#   define IW_MKF_S3EADMOB_BUILD 1
#endif
#ifndef IW_PLATFORM_IPHONE
#   define IW_PLATFORM_IPHONE 1
#endif
#ifndef IW_SDK
#   define IW_SDK 1
#endif
#ifndef IW_TRACE_CHANNEL_ADMOB
#   define IW_TRACE_CHANNEL_ADMOB 1
#endif
#ifndef IW_TRACE_CHANNEL_ADMOB_VERBOSE
#   define IW_TRACE_CHANNEL_ADMOB_VERBOSE 2
#endif
#ifndef S3E_BUILD_EXT
#   define S3E_BUILD_EXT 1
#endif
#ifndef S3E_EXT_ADMOB
#   define S3E_EXT_ADMOB 1
#endif

/* including "extra_body" specified by the mkb plugin */

#if !defined I3D_ARCH_ARM && !defined I3D_ARCH_X86 && !defined I3D_ARCH_PS3 && !defined I3D_ARCH_X360
    #if defined __ARMCC_VERSION || defined __arm__
        #define I3D_ARCH_ARM
    #else
        #define I3D_ARCH_X86
        #define I3D_ARCH_I386
    #endif
#endif

#if defined I3D_ARCH_X86 && !defined __i386__
    #define __i386__
#endif

#if defined I3D_ARCH_ARM && !defined __ARM__
    #define __ARM__
#endif
