#pragma once
#include "ILogger.h"
#include "LogLevelConverter.h"


namespace Matrix
{
	class LoggerBase :public ILogger
	{
	public:
		LoggerBase();

		~LoggerBase();

		bool isEnabled(LogLevel level) override;

		ILogger& debug(std::string message) override;

		ILogger& trace(std::string message) override;

		ILogger& info(std::string message) override;

		ILogger& warning(std::string message) override;

		ILogger& error(std::string message) override;

		ILogger& fatal(std::string message) override;

	protected:
		std::string format(LogLevel level, std::string message, int eveintId = 0, std::exception* exception = nullptr, TextFormatter formatter = TextFormatter::DefaultTextFormatter());

		LogLevelConverter mConverter;

		std::string wrapText(std::string value);
	};

}