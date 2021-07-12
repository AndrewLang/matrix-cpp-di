#pragma once
#include "logging/ILoggerFactory.h"
#include "logging/LoggerFactory.h"
#include "logging/VsOutputLoggerProvider.h"

#include <memory>

using std::shared_ptr;

namespace Matrix
{
	class LoggerCreator
	{
	public:
		LoggerCreator();
		~LoggerCreator();

		static shared_ptr<ILoggerFactory> createFactory()
		{
			auto factory = std::make_shared<LoggerFactory>();

			factory->useProvider<VsOutputLoggerProvider>();

			return factory;
		}
	};

}