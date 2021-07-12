#pragma once
#include "LoggerBase.h"


namespace Matrix
{
	class VsOutputLogger :public LoggerBase
	{
	public:
		VsOutputLogger() = delete;

		VsOutputLogger(const std::string & name);

		VsOutputLogger(const VsOutputLogger& logger);

		~VsOutputLogger();


		ILogger& log(LogLevel level, std::string message, int eveintId, std::exception* exception, TextFormatter formatter) override;

	};

}