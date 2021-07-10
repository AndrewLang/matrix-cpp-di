#pragma once
#include "ILoggerProvider.h"

namespace Matrix
{
	class ConsoleLoggerProvider : public ILoggerProvider
	{
	public:
		ConsoleLoggerProvider();
		~ConsoleLoggerProvider();

		std::shared_ptr<ILogger> createLogger(std::string name) override;
	};


}