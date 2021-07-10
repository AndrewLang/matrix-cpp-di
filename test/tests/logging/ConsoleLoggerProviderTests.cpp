#include "pch.h"
#include "gtest/gtest.h"
#include "logging/ConsoleLoggerProvider.h"
#include "logging/ILogger.h"

namespace Matrix
{
	TEST(ConsoleLoggerProviderTests, Constructor) {
		ConsoleLoggerProvider provider;
	}
	TEST(ConsoleLoggerProviderTests, CreateLogger)
	{
		ConsoleLoggerProvider provider;
		auto logger = provider.createLogger("test");
				
		ASSERT_EQ("test", logger->name);
	}
}