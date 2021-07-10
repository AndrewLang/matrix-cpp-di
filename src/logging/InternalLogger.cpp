#include "logging/InternalLogger.h"


namespace Matrix
{
	InternalLogger::InternalLogger(std::shared_ptr<ILoggerFactory> factory, std::string loggerName)
		: mFactory(factory)
	{
		name = loggerName;
		initialize();
	}
	
	InternalLogger::~InternalLogger()
	{
		mLoggers.clear();
	}

	ILogger & InternalLogger::log(LogLevel level, std::string message, int eveintId, std::exception* exception, TextFormatter formatter)
	{
		std::vector<std::exception> exceptions;
		for (auto logger : mLoggers)
		{
			try
			{
				logger->log(level, message, eveintId, exception, formatter);
			}
			catch (const std::exception& ex)
			{
				exceptions.push_back(ex);
			}
		}

		if (exceptions.size() > 0)
		{
			throw std::runtime_error("An error occurred while writing to logger(s).");
		}

		return *this;
	}

	bool InternalLogger::isEnabled(LogLevel level)
	{
		for (auto logger : mLoggers)
		{
			if (logger->isEnabled(level))
			{
				return true;
			}
		}
		return false;
	}

	ILogger & InternalLogger::debug(std::string message)
	{
		log(LogLevel::Debug, message);

		return *this;
	}

	ILogger & InternalLogger::trace(std::string message)
	{
		log(LogLevel::Trace, message);
		return *this;
	}

	ILogger & InternalLogger::info(std::string message)
	{
		log(LogLevel::Information, message);
		return *this;
	}

	ILogger & InternalLogger::warning(std::string message)
	{
		log(LogLevel::Warning, message);
		return *this;
	}

	ILogger & InternalLogger::error(std::string message)
	{
		log(LogLevel::Error, message);
		return *this;
	}

	ILogger & InternalLogger::fatal(std::string message)
	{
		log(LogLevel::Fatal, message);
		return *this;
	}

	void InternalLogger::addProvider(std::shared_ptr<ILoggerProvider> provider)
	{
		auto logger = provider->createLogger(name);
		mLoggers.push_back(logger);
	}

	void InternalLogger::initialize()
	{
		auto providers = mFactory->getProviders();
		for (auto provider : providers)
		{
			mLoggers.push_back(provider->createLogger(name));
		}
	}

}