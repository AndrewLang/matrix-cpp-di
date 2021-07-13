#include "pch.h"
#include "gtest/gtest.h"
#include "logging/VsOutputLogger.h"
#include "logging/LogMessageName.h"
#include "common/ConstStrings.h"

#include <memory>

namespace Matrix
{
	TEST(VsOutputLoggerTests, Constructor)
	{
		VsOutputLogger logger("test");

		EXPECT_EQ("test", logger.name);
	}

	TEST(VsOutputLoggerTests, LoggerMessages)
	{
		VsOutputLogger logger("test");

		EXPECT_EQ("test", logger.name);

		logger.debug("this is debug")
			.error("this is error")
			.fatal("this is fatal")
			.info("this is info")
			.trace("this is trace")
			.warning("this is warning");
	}

	TEST(VsOutputLoggerTests, LogWithGroup)
	{
		VsOutputLogger logger("test");

		EXPECT_EQ("test", logger.name);

		logger
			.startGroup("test group")
			.debug("this is debug")
			.error("this is error")
			.fatal("this is fatal")
			.info("this is info")
			.trace("this is trace")
			.warning("this is warning")
			.endGroup();
	}

	TEST(VsOutputLoggerTests, LogMessageWithName) {
		std::shared_ptr<ILogger> logger = std::make_shared<VsOutputLogger>("test");

		EXPECT_EQ("test", logger->name);

		logger->info(N("Iron man"), "1. this is a test")
			.info(N("Spider man"), "2. this is a test")
			.info(N("Caption American"), "3. this is a test")
			.info(N("Hulk"), "4. this is a test");
	}
}