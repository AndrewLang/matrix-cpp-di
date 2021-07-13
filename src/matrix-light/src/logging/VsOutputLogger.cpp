#include "logging/VsOutputLogger.h"
#include "logging/VsOutput.h"
#include "common/StringExtensions.h"
#include "common/ConstStrings.h"

namespace Matrix
{
	VsOutputLogger::VsOutputLogger(const std::string & loggerName)
	{
		name = loggerName;
	}

	VsOutputLogger::VsOutputLogger(const VsOutputLogger & logger)
	{
		name = logger.name;
	}


	VsOutputLogger::~VsOutputLogger()
	{
	}

	ILogger & VsOutputLogger::log(LogLevel level, std::string message, int eveintId, std::exception* exception, TextFormatter formatter)
	{
		auto text = StringExtensions::wrapBySquare(name) + ConstStrings::Space + format(level, message, eveintId, exception, formatter);
		
		VsOutput::debugLine(text);
		
		return *this;
	}
}