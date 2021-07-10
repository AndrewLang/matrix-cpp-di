#pragma once
#pragma warning(disable:4251)
#pragma warning(disable:4221)


#ifndef PCH_H
#define PCH_H


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
// #include <windows.h>


#if defined(_WIN32)
//  Windows 
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#define WIN_C_EXPORT __declspec(dllexport)
#define LINUX_C_EXPORT
#define CALLING_CONV __cdecl
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif

#elif defined(__linux__)
//  Linux
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#define LINUX_C_EXPORT __attribute__((visibility("default")))
#define WIN_C_EXPORT
#define CALLING_CONV

#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif

#else
//  do nothing and hope for the best?
#define EXPORT
#define IMPORT
#define WIN_EXPORT
#define WIN_IMPORT
#define CALLING_CONV
#pragma warning Unknown dynamic link import/export semantics.
#endif


#if defined(PXIRESOURCEMANAGERCOMMON_EXPORTS)
#define DECLSPEC EXPORT
#define LINUX_C_DECLSPEC LINUX_C_EXPORT
#define WIN_C_DECLSPEC WIN_C_EXPORT
#else
#define DECLSPEC
#define WIN_C_DECLSPEC
#define LINUX_C_DECLSPEC
#endif


#endif //PCH_H