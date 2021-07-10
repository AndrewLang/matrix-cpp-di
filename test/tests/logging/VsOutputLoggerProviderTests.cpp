#include "pch.h"
#include "gtest/gtest.h"
#include "logging/VsOutputLoggerProvider.h"
#include "logging/ILogger.h"

namespace Matrix
{
	TEST(VsOutputLoggerProviderTests, Constructor) 
	{
		VsOutputLoggerProvider provider;
	}

	TEST(VsOutputLoggerProviderTests, CreateLogger) {
		VsOutputLoggerProvider provider;

		auto logger = provider.createLogger("test");

		EXPECT_EQ("test", logger->name);
	}
}