#include "logging/ConsoleLogger.h"
#include "logging/LogLevelConverter.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace Matrix
{
	ConsoleLogger::ConsoleLogger(const std::string & loggerName)
	{
		name = loggerName;
		mCreatedDate = StringExtensions::getTimestamp();
	}

	ConsoleLogger::ConsoleLogger(const ConsoleLogger& logger)
	{
		name = logger.name;
	}

	ConsoleLogger::~ConsoleLogger()
	{
		
	}
	
	ILogger & ConsoleLogger::log(LogLevel level, std::string message, int eveintId, std::exception* exception, TextFormatter formatter)
	{
		auto text = format(level, message, eveintId, exception, formatter);

		LogLevelConverter converter;

		cout << StringExtensions::wrapBySquare(StringExtensions::getTimestamp()) << StringExtensions::wrapBySquare(name) << text << endl;

		return *this;
	}
}