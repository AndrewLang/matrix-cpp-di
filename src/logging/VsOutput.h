#pragma once
#include "common/TextFormatter.h"
#include "common/StringExtensions.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <time.h>
#include <stdio.h>

namespace Matrix
{
	class VsOutput
	{
	public:

		template<typename ... Args >
		static void debug(Args&& ... args)
		{
			TextFormatter formatter;
			auto message = formatter.format(args...);

			message = StringExtensions::wrapBySquare(StringExtensions::getTimestamp()) + SPACE + message;

			logMessage(message);

		}

		template<typename ... Args >
		static void debugLine(Args&& ... args)
		{
			TextFormatter formatter;
			auto message = formatter.format(args...);
			message = StringExtensions::wrapBySquare(StringExtensions::getTimestamp()) + SPACE + message + StringExtensions::NewLine;

			logMessage(message);
		}

		template<typename ... Args >
		static void writeWithName(std::string name, Args&& ... args)
		{
			TextFormatter formatter;
			auto message = StringExtensions::wrapBySquare(StringExtensions::getTimestamp())
				+ SPACE
				+ StringExtensions::paddingString(name)
				+ SPACE
				+ formatter.format(args...)
				+ StringExtensions::NewLine;

			logMessage(message);
		}

	private:

		inline static void logMessage(std::string message)
		{
			/*
			Force log message without unicode
			*/

			//auto lp = StringExtensions::toWString(message).c_str();
			//OutputDebugString(lp);			

#if defined(_WIN32)
			OutputDebugStringA(message.c_str());
#endif
		}
	};

}
