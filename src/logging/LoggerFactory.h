#pragma once
#include "ILoggerFactory.h"
#include "InternalLogger.h"

#include <map>
#include <string>
#include <memory>


namespace Matrix
{
	class LoggerFactory : public ILoggerFactory, public std::enable_shared_from_this<LoggerFactory>
	{
	public:
		LoggerFactory();

		~LoggerFactory();

		std::shared_ptr<ILogger> createLogger(std::string name) override;

		void addProvider(std::shared_ptr<ILoggerProvider> provider) override;

		std::vector<std::shared_ptr<ILoggerProvider>> getProviders() override;
				

	private:
		std::vector<std::shared_ptr<ILoggerProvider>> mProviders;

		std::map<std::string, std::shared_ptr<InternalLogger>> mLoggers;
	};

}