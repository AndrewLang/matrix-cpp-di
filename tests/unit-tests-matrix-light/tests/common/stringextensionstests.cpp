#include "gtest/gtest.h"
#include "common/StringExtensions.h"
#include "logging/VsOutput.h"
#include <functional>


namespace Matrix
{
	using std::string;
	using std::vector;
	using std::wstring;

	TEST(StringExtensionsTests, SplitWithDefault) {
		string text = "this is a test!";
		vector<string> result = StringExtensions::split(text);

		ASSERT_EQ(4, result.size());
		ASSERT_EQ("this", result[0]);
		ASSERT_EQ("is", result[1]);
		ASSERT_EQ("a", result[2]);
		ASSERT_EQ("test!", result[3]);
	}

	TEST(StringExtensionsTests, SplitWithColon) {
		string text = "section:key";
		vector<string> result = StringExtensions::split(text, ':');

		ASSERT_EQ(2, result.size());
		ASSERT_EQ("section", result[0]);
		ASSERT_EQ("key", result[1]);
	}

	TEST(StringExtensionsTests, SplitMultipleTestCode) {
		const string delimiters = "_&";
		string value = "ven_8086&dev_15b7&subsys_81c5103c&rev_00";

		std::function isDelimiter = [](const string& delimiters, char c)
		{
			for (auto cValue : delimiters)
			{
				if (cValue == c)
					return true;
			}
			return false;
		};

		std::stringstream stringStream(value);
		std::string word; char c;
		vector<string> result;

		while (stringStream) {
			word.clear();

			// Read word
			c = stringStream.get();
			while (!isDelimiter(delimiters, c))
			{
				word.push_back(c);
				c = stringStream.get();
				if (c == EOF)
					break;
			}

			result.push_back(word);
		}

		ASSERT_EQ(8, result.size());

	}

	TEST(StringExtensionsTests, SplitMultiple) {
		vector<string> delimiters = { "_", "&"  };
		auto result = StringExtensions::split("ven_8086&dev_15b7&subsys_81c5103c&rev_00", delimiters);

		for (auto item : result)
		{
			VsOutput::writeWithName("Segment:", item);
		}

		ASSERT_EQ(8, result.size());
		ASSERT_EQ("ven", result[0]);
		ASSERT_EQ("8086", result[1]);
		ASSERT_EQ("subsys", result[4]);
		ASSERT_EQ("00", result[7]);
	}

	TEST(StringExtensionsTests, Replace) {
		ASSERT_EQ("test hello world", StringExtensions::replace("test hello hi", "hi", "world"));
		ASSERT_EQ("C:\\program files\\keysight\\iols", StringExtensions::replace(R"(C:\program files\keysight\iols)", R"(\)", R"(\)"));
	}

	TEST(StringExtensionsTests, CompareIgnoreCase) {
		ASSERT_TRUE(StringExtensions::compareIgnoreCase("hello", "HELLO"));
		ASSERT_TRUE(StringExtensions::compareIgnoreCase("HeLLo", "HEllO"));

		ASSERT_FALSE(StringExtensions::compareIgnoreCase("HeLLo w", "HEllO world"));
	}

	TEST(StringExtensionsTests, CompareIgnoreCaseTrim) {
		ASSERT_TRUE(StringExtensions::compareTrimIgnoreCase("hello ", "HELLO"));
		ASSERT_TRUE(StringExtensions::compareTrimIgnoreCase(" HeLLo", "HEllO"));

		ASSERT_TRUE(StringExtensions::compareTrimIgnoreCase("hello$", "HELLO", "$"));
		ASSERT_TRUE(StringExtensions::compareTrimIgnoreCase("$HeLLo", "HEllO", "$"));

		ASSERT_FALSE(StringExtensions::compareTrimIgnoreCase("HeLLo w", "HEllO world"));
	}
	TEST(StringExtensionsTests, IsNullOrEmpty) {
		string value;
		ASSERT_TRUE(StringExtensions::isNullOrEmpty(value));
		ASSERT_TRUE(StringExtensions::isNullOrEmpty(""));
		ASSERT_FALSE(StringExtensions::isNullOrEmpty(" "));
		ASSERT_FALSE(StringExtensions::isNullOrEmpty("text"));
	}

	TEST(StringExtensionsTests, NotNullOrEmpty) {
		string value;
		ASSERT_FALSE(StringExtensions::notNullOrEmpty(value));
		ASSERT_FALSE(StringExtensions::notNullOrEmpty(""));
		ASSERT_TRUE(StringExtensions::notNullOrEmpty(" "));
		ASSERT_TRUE(StringExtensions::notNullOrEmpty("text"));
	}

	TEST(StringExtensionsTests, IndexOf) {
		string value = "PCIROOT(0)#PCI(1D00)#PCI(0000)#PCI(0300)";
		int pos = StringExtensions::indexOf(value, '(');
		ASSERT_EQ(pos, 7);
		pos = StringExtensions::indexOf(value, ')');
		ASSERT_EQ(pos, 9);

		pos = StringExtensions::indexOf(value, "ROOT");
		ASSERT_EQ(pos, 3);
	}

	TEST(StringExtensionsTests, TextBetween) {
		ASSERT_EQ("0", StringExtensions::textBetween("PCIROOT(0)#PCI(1D00)#PCI(0000)#PCI(0300)", '(', ')'));
		ASSERT_EQ("t with s", StringExtensions::textBetween("this is a tex(t with s)omething", '(', ')'));
	}
	
	TEST(StringExtensionsTests, ToLower) {
		ASSERT_EQ("", StringExtensions::toLower(""));
		ASSERT_EQ("hello", StringExtensions::toLower("Hello"));
		ASSERT_EQ("hello", StringExtensions::toLower("HeLLo"));
		ASSERT_EQ("hi", StringExtensions::toLower("HI"));
		ASSERT_EQ(R"(\hi\world)", StringExtensions::toLower(R"(\HI\world)"));
		ASSERT_EQ(R"(pci\ven_8086&dev_15b7&subsys_81c5103c&rev_00\3&11583659&0&fe)", StringExtensions::toLower(R"(PCI\VEN_8086&DEV_15B7&SUBSYS_81C5103C&REV_00\3&11583659&0&FE)"));
	}

	TEST(StringExtensionsTests, ToUpper) {
		ASSERT_EQ("", StringExtensions::toUpper(""));
		ASSERT_EQ("HELLO", StringExtensions::toUpper("hello"));
		ASSERT_EQ("HELLO", StringExtensions::toUpper("HeLLo"));
		ASSERT_EQ("HI", StringExtensions::toUpper("HI"));
		ASSERT_EQ(R"(PCI\VEN_8086&DEV_15B7&SUBSYS_81C5103C&REV_00\3&11583659&0&FE)", StringExtensions::toUpper(R"(PCI\VEN_8086&DEV_15B7&SUBSYS_81C5103C&REV_00\3&11583659&0&FE)"));
	}

	TEST(StringExtensionsTests, LiteralString) {
		ASSERT_EQ("test", StringExtensions::literalString("test"));
		ASSERT_EQ("pci\ven_8086&dev_15b7&subsys_81c5103c&rev_00\3&11583659&0&fe", StringExtensions::literalString("pci\ven_8086&dev_15b7&subsys_81c5103c&rev_00\3&11583659&0&fe"));
	}

	TEST(StringExtensionsTests, ConvertToValue) {
		ASSERT_EQ(10, StringExtensions::convertTo<int>("10"));
	}

	TEST(StringExtensionsTests, ParseHex) {
		ASSERT_EQ(5559, StringExtensions::parseHex("15b7"));
	}

	TEST(StringExtensionsTests, StringToWString) {
		string value("test");
		wstring actual = StringExtensions::toWString(value);
		ASSERT_EQ(actual, L"test");
	}

	TEST(StringExtensionsTests, WStringToString) {
		wstring value(L"test");
		string actual = StringExtensions::toString(value);
		ASSERT_EQ(actual, "test");
	}

	TEST(StringExtensionsTests, StartsWith) {		
		ASSERT_TRUE(StringExtensions::startsWith("this is a test", "this"));
		ASSERT_TRUE(StringExtensions::startsWith("\\this is a test", "\\"));
		ASSERT_FALSE(StringExtensions::startsWith("this is a test", "This"));

		ASSERT_FALSE(StringExtensions::startsWith("this is a test", 's'));
		ASSERT_TRUE(StringExtensions::startsWith("this is a test", 't'));
	}

	TEST(StringExtensionsTests, EndsWith) {
		ASSERT_TRUE(StringExtensions::endsWith("this is a test", "test"));
		ASSERT_TRUE(StringExtensions::endsWith("this is a test\\", "\\"));
		ASSERT_FALSE(StringExtensions::endsWith("this is a test", "Test"));

		ASSERT_FALSE(StringExtensions::endsWith("this is a test", 's'));
		ASSERT_TRUE(StringExtensions::endsWith("this is a test", 't'));
	}

	TEST(StringExtensionsTests, PaddingString) {
		ASSERT_EQ(StringExtensions::paddingString("test").size(), StringExtensions::Padding);
	}

	TEST(StringExtensionsTests, WrapBySquare) {
		ASSERT_EQ(StringExtensions::wrapBySquare("test"), "[test]");
	}

	TEST(StringExtensionsTests, GetTimestemp) {
		ASSERT_FALSE(StringExtensions::isNullOrEmpty(StringExtensions::getTimestamp()));
	}

	TEST(StringExtensionsTests, NameAlias) {
		ASSERT_EQ(Strings::wrapBySquare("test"), "[test]");
	}

	TEST(StringExtensionsTests, Contains) {
		ASSERT_TRUE(Strings::contains("this is test", "test", false));
		ASSERT_FALSE(Strings::contains("this is test", "Test", false));
	}

	TEST(StringExtensionsTests, ContainsIgnoreCase) {
		ASSERT_TRUE(Strings::contains("this is test", "test"));
		ASSERT_TRUE(Strings::contains("this is test", "Test"));
	}

	TEST(StringExtensionsTests, TrimStart) {
		ASSERT_EQ(Strings::trimStart(" start"), "start");
		ASSERT_EQ(Strings::trimStart("@start", "@"), "start");
		ASSERT_EQ(Strings::trimStart("@!start", "@!"), "start");
		ASSERT_EQ(Strings::trimStart("@!start", "!@"), "start");
	}

	TEST(StringExtensionsTests, TrimEnd) {
		ASSERT_EQ(Strings::trimEnd("start "), "start");
		ASSERT_EQ(Strings::trimEnd("start@", "@"), "start");
		ASSERT_EQ(Strings::trimEnd("start@!", "@!"), "start");
		ASSERT_EQ(Strings::trimEnd("start@!", "!@"), "start");
	}

	TEST(StringExtensionsTests, Trim) {
		ASSERT_EQ(Strings::trim(" start "), "start");
		ASSERT_EQ(Strings::trim("@start@", "@"), "start");
		ASSERT_EQ(Strings::trim("@!start@!", "@!"), "start");
		ASSERT_EQ(Strings::trim("!@start@!", "!@"), "start");
		ASSERT_EQ(Strings::trim("start\0\0", "\0"), "start");
	}

	TEST(StringExtensionsTests, CharsToString) {
		vector<char> chars = { 's', 't', 'a', 'r', 't' , '\0', '\0'};

		ASSERT_EQ("start", Strings::toString(chars));
	}
}