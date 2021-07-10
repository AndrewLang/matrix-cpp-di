#include "pch.h"
#include "gtest/gtest.h"
#include "common/TextFormatter.h"

namespace Matrix
{

	TEST(TextFormatterTest, DefaultFormatter)
	{		
		auto formatter = TextFormatter::DefaultTextFormatter();
		auto formatter2 = TextFormatter::DefaultTextFormatter();
	}

	TEST(TextFormatterTest, FormatSingle)
	{
		TextFormatter formatter;
		std::string expect = "hello world";
		auto actual = formatter.format(expect);

		EXPECT_EQ(expect + Connectivity::SPACE, actual);
	}

	TEST(TextFormatterTest, FormatMultiple)
	{
		TextFormatter formatter;
		std::string expect = "hello";
		std::string expect1 = "world";

		auto actual = formatter.format(expect, expect1);

		EXPECT_EQ(expect + Connectivity::SPACE + expect1 + Connectivity::SPACE, actual);
	}
}