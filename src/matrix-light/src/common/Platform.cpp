#include "common/Platform.h"

#include <windows.h>

namespace Matrix
{
	bool Platform::is64Bit()
	{

#if defined(_WIN64)
		return true;  // 64-bit code implies a 64-bit OS
#elif defined(_WIN32)
		// 32-bit code runs on a 64-bit OS, if IsWow64Process returns TRUE
		BOOL value = FALSE;
		return ::IsWow64Process(GetCurrentProcess(), &value) && value;
#elif defined(__linux__)
#if __x86_64__ || __ppc64__
		return true;
#else
		return false;
#endif
#else
#error Unexpected platform.
#endif
	}
}