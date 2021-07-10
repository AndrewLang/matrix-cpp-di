#include "pch.h"
#include "gtest/gtest.h"
#include "logging/LogLevelConverter.h"


namespace Matrix
{	TEST(LogLevelConverterTests, ConvertToString) {
		LogLevelConverter converter;

		EXPECT_EQ("Debug", converter.toString(LogLevel::Debug));
		EXPECT_EQ("Trace", converter.toString(LogLevel::Trace));
		EXPECT_EQ("Information", converter.toString(LogLevel::Information));
		EXPECT_EQ("Warning", converter.toString(LogLevel::Warning));
		EXPECT_EQ("Error", converter.toString(LogLevel::Error));
		EXPECT_EQ("Fatal", converter.toString(LogLevel::Fatal));
		EXPECT_EQ("None", converter.toString(LogLevel::None));
	}

}