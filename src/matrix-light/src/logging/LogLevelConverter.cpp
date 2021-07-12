#include "logging/LogLevelConverter.h"

namespace Matrix
{
	LogLevelConverter::LogLevelConverter()
	{
		mValues[LogLevel::Trace] = "Trace";
		mValues[LogLevel::Debug] = "Debug";
		mValues[LogLevel::Information] = "Information";
		mValues[LogLevel::Warning] = "Warning";
		mValues[LogLevel::Error] = "Error";
		mValues[LogLevel::Fatal] = "Fatal";
		mValues[LogLevel::None] = "None";
	}

	LogLevelConverter::~LogLevelConverter()
	{
		mValues.clear();
	}

	std::string LogLevelConverter::toString(LogLevel level)
	{
		auto iterator = mValues.find(level);
		if (iterator != mValues.end())
		{
			return iterator->second;
		}
		return "";
	}
}
