#pragma once

#include <string>
#include <vector>
#include <Windows.h>

namespace Matrix
{
	class WinStringExtensions
	{
	public:
		static TCHAR* convertToTchar(std::string value)
		{
			TCHAR * result = new TCHAR[value.size() + 1];
			result[value.size()] = 0;
			
			std::copy(value.begin(), value.end(), result);

			return result;
		}

		static std::string convertToString(const TCHAR raw[])
		{
			std::wstring wString(raw);
			std::string value(wString.begin(), wString.end());
			return value;
		}
	};

	using WinStrings = WinStringExtensions;
}