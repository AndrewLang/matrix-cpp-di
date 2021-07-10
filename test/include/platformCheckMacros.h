#pragma once

// This file outputs below pre-defined macros to check OS and compiler.
// -- PLATFORM_OS_NAME
// -- PLATFORM_OS_WINDOWS
// -- PLATFORM_OS_LINUX
// -- PLATFORM_OS_IOS
// -- PLATFORM_OS_OSX
// -- PLATFORM_BITS_NAME
// -- PLATFORM_BITS_64
// -- PLATFORM_BITS_32
// -- PLATFORM_CC_NAME
// -- PLATFORM_CC_VC
// -- PLATFORM_CC_GCC
// -- PLATFORM_CC_MINGW


// Operating System. We only support Windows & Linux currently.

#if defined(__linux__) || defined(linux) || defined(__linux) || defined(__LINUX__) || defined(LINUX) || \
    defined(_LINUX)
#   define PLATFORM_OS_NAME "Linux"
#   define PLATFORM_OS_LINUX
#elif defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || \
    defined(__WIN32__) || defined(_WINDOWS)
#   define PLATFORM_OS_NAME "Windows"
#   define PLATFORM_OS_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
#define PLATFORM_OS_NAME "ios" // Apple iOS
#define PLATFORM_OS_IOS
#elif TARGET_OS_IPHONE == 1
#define PLATFORM_OS_NAME "ios" // Apple iOS
#define PLATFORM_OS_IOS
#elif TARGET_OS_MAC == 1
#define PLATFORM_OS_NAME "OSX" // Apple OSX
#define PLATFORM_OS_OSX
#endif
#else
#   define PLATFORM_OS_NAME "Unknown"
#   error unsupported os
#endif

// Bits.
#if defined(_WIN64) || defined(WIN64) || defined(__amd64__) || defined(__amd64) || defined(__LP64__) || \
    defined(_LP64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(__ia64__) || \
    defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64)
#   define PLATFORM_BITS_NAME "64"
#   define PLATFORM_BITS_64
#elif defined(_WIN32) || defined(WIN32) || defined(__32BIT__) || defined(__ILP32__) || defined(_ILP32) || \
    defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || \
    defined(__i386) || defined(_M_IX86) || defined(__X86__) || defined(_X86_) || defined(__I86__)
#   define PLATFORM_BITS_NAME "32"
#   define PLATFORM_BITS_32
#else
#   define PLATFORM_BITS_NAME "Unknown"
#   error unknown bits
#endif

// Compiler.
#if defined(_MSC_VER)
#	define PLATFORM_CC_NAME "VC"
#	define PLATFORM_CC_VC
#elif defined(__MINGW32__) || defined(__MINGW64__)
#	define PLATFORM_CC_NAME "MINGW"
#	define PLATFORM_CC_MINGW
#	define PLATFORM_CC_GCC
#elif defined(__GNUG__) || defined(__GNUC__)
#	define PLATFORM_CC_NAME "GCC"
#	define PLATFORM_CC_GCC
#else
#	define PLATFORM_CC_NAME "Unknown"
#   error unknown compiler
#endif