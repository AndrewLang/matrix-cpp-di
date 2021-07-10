#pragma once
#include "ILoggerProvider.h"

namespace Matrix
{
	class VsOutputLoggerProvider : public ILoggerProvider
	{
	public:
		VsOutputLoggerProvider();

		~VsOutputLoggerProvider();

		std::shared_ptr<ILogger> createLogger(std::string name) override;
	};
}
