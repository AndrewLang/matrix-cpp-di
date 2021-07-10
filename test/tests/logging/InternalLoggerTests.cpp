#include "gtest/gtest.h"
#include "logging/InternalLogger.h"
#include "logging/ILogger.h"
#include "logging/LoggerFactory.h"
#include "logging/ConsoleLoggerProvider.h"

namespace Matrix
{
	TEST(InternalLoggerTests, Constructor) 
	{
		/*auto factory = std::make_shared<LoggerFactory>();
		InternalLogger logger(factory, "test");

		EXPECT_EQ("test", logger.name);

		logger.debug("test");*/
	}
	TEST(InternalLoggerTests, AddProvider)
	{
		/*auto factory = std::make_shared<LoggerFactory>();
		auto provider = std::make_shared<ConsoleLoggerProvider>();


		InternalLogger logger(factory, "test");

		logger.addProvider(provider);
		
		EXPECT_EQ("test", logger.name);

		logger.debug("test");*/

	}
	
}