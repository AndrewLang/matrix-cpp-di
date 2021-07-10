#include "gtest/gtest.h"
#include "configuration/MemoryConfigurationProvider.h"
#include "configuration/IConfiguration.h"
#include "logging/VsOutput.h"

namespace Matrix
{
	using std::string;
	using std::vector;

	TEST(MemoryConfigurationProviderTests, Constructor) {
		MemoryConfigurationProvider provider;
	}

	TEST(MemoryConfigurationProviderTests, Load) {
		MemoryConfigurationProvider provider;
		provider.load();
	}

	TEST(MemoryConfigurationProviderTests, Save) {
		MemoryConfigurationProvider provider;
		//provider.save();
	}

	TEST(MemoryConfigurationProviderTests, SetGet) {
		MemoryConfigurationProvider provider;

		provider
			.set("name", "resource")
			.set("version", "1.0");

		std::string value;
		ASSERT_EQ(true, provider.tryGet("name", value));
		ASSERT_EQ("resource", value);

		ASSERT_EQ(true, provider.tryGet("version", value));
		ASSERT_EQ("1.0", value);

		ASSERT_EQ(false, provider.tryGet("description",  value, "test"));
		ASSERT_EQ("test", value);
	}

	TEST(MemoryConfigurationProviderTests, GetChildKeys) {
		MemoryConfigurationProvider provider;

		provider
			.set("name", "resource")
			.set("version", "1.0")
			.set("section1:name", "manager")
			.set("section1:version", "0.1")
			.set("section2:name", "demo")
			.set("section2:version", "0.2")
			;

		vector<string> keys = { "early1", "early2" };
		auto actual = provider.getChildKeys(keys, "", ":");

		for (auto item : actual)
		{
			VsOutput::debug("Key: ", item, "\n");
		}

		ASSERT_EQ(8, actual.size());

	}
}