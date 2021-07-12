#pragma once
#include <memory>
#include <string>

namespace Matrix
{
	class ILogger;

	class ILoggerProvider
	{
	public:
		virtual std::shared_ptr<ILogger> createLogger(std::string name) = 0;
	};

}