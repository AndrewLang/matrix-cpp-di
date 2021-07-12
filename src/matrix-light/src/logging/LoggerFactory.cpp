#include "logging/LoggerFactory.h"

namespace Matrix
{
	
	LoggerFactory::LoggerFactory()
	{
		
	}

	LoggerFactory::~LoggerFactory()
	{
		mProviders.clear();
		mLoggers.clear();
	}

	std::shared_ptr<ILogger> LoggerFactory::createLogger(std::string name)
	{
		auto finder = mLoggers.find(name);

		if (finder == mLoggers.end()) 
		{
			auto pointer = shared_from_this();

			auto loggerPtr = std::make_shared<InternalLogger>(pointer, name);

			mLoggers.insert(std::make_pair(name, loggerPtr));

			return loggerPtr;
		}
		else
		{
			return finder->second;
		}
	}

	void LoggerFactory::addProvider(std::shared_ptr<ILoggerProvider> provider)
	{
		mProviders.push_back(provider);

		for (auto &pair : mLoggers)
		{
			pair.second->addProvider(provider);
		}
	}

	std::vector<std::shared_ptr<ILoggerProvider>> LoggerFactory::getProviders()
	{
		return mProviders;
	}
}