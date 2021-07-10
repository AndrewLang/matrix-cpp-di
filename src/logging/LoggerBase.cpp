#include "logging/LoggerBase.h"

namespace Matrix
{
	using std::string;


	LoggerBase::LoggerBase()
	{
	}


	LoggerBase::~LoggerBase()
	{
	}

	bool Connectivity::LoggerBase::isEnabled(LogLevel level)
	{
		return true;
	}

	ILogger & LoggerBase::debug(std::string message)
	{
		log(LogLevel::Debug, message);
		return *this;
	}

	ILogger & LoggerBase::trace(std::string message)
	{
		log(LogLevel::Trace, message);
		return *this;
	}

	ILogger & LoggerBase::info(std::string message)
	{
		log(LogLevel::Information, message);
		return *this;
	}

	ILogger & LoggerBase::warning(std::string message)
	{
		log(LogLevel::Warning, message);
		return *this;
	}

	ILogger & LoggerBase::error(std::string message)
	{
		log(LogLevel::Error, message);
		return *this;
	}

	ILogger & LoggerBase::fatal(std::string message)
	{
		log(LogLevel::Fatal, message);
		return *this;
	}
	
	std::string LoggerBase::format(LogLevel level, std::string message, int eveintId, std::exception* exception, TextFormatter formatter)
	{
		string levelText = level == LogLevel::None ?
			"" : wrapText(mConverter.toString(level));

		if (exception)
		{
			return formatter.format(levelText, message, exception->what());
		}
		return formatter.format(levelText, message);
	}

	string LoggerBase::wrapText(string value)
	{
		return "[" + value + "]";
	}
}