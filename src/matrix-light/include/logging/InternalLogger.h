#pragma once

#include "ILogger.h"
#include "ILoggerFactory.h"
#include "ILoggerProvider.h"

#include <memory>
#include <string>

namespace Matrix
{
	class InternalLogger : public ILogger
	{
	public:
		InternalLogger(std::shared_ptr<ILoggerFactory> factory, std::string name);		

		InternalLogger() = delete;

		InternalLogger(const InternalLogger &) = delete;

		InternalLogger& operator=(const InternalLogger&) = delete;

		~InternalLogger();

		ILogger& log(LogLevel level, std::string message, int eveintId = 0, std::exception* exception = nullptr, TextFormatter formatter = TextFormatter::DefaultTextFormatter()) override;

		bool isEnabled(LogLevel level) override;

		void addProvider(std::shared_ptr<ILoggerProvider> provider);

		ILogger& debug(std::string message) override;

		ILogger& trace(std::string message) override;

		ILogger& info(std::string message) override;

		ILogger& warning(std::string message) override;

		ILogger& error(std::string message) override;

		ILogger& fatal(std::string message) override;

	private:
		std::shared_ptr<ILoggerFactory> mFactory;
	
		std::vector<std::shared_ptr<ILogger>> mLoggers;

		void initialize();
	};

}