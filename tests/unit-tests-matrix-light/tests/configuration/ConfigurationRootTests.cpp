#include "gtest/gtest.h"
#include "configuration/ConfigurationRoot.h"
#include "configuration/MemoryConfigurationProvider.h"
#include "logging/VsOutput.h"

namespace Matrix
{
	using std::string;
	using std::vector;
	using std::shared_ptr;

	TEST(ConfigurationRootTests, Constructor) {

		vector<shared_ptr<IConfigurationProvider>> providers;

		ConfigurationRoot root(providers);
	}

	TEST(ConfigurationRootTests, GetSetPropertyValues) {
		auto provider = std::make_shared< MemoryConfigurationProvider>();

		(*provider)
			.set("name", "resource")
			.set("version", "1.0")
			.set("year", "2019")
			.set("section1:name", "manager")
			.set("section1:version", "0.1")
			.set("section2:name", "demo")
			.set("section2:version", "0.2")
			;
		

		vector<shared_ptr<IConfigurationProvider>> providers;
		providers.push_back(provider);


		auto root = std::make_shared<ConfigurationRoot>(providers);
		
		std::string value;
		ASSERT_TRUE(root->tryGet("name", value));
		ASSERT_EQ("resource", value);

		ASSERT_TRUE(root->tryGet("version", value));
		ASSERT_EQ("1.0", value);

		ASSERT_TRUE(root->tryGet("section1:name", value));
		ASSERT_EQ("manager", value);


		ASSERT_TRUE(root->tryGet("section2:version", value));
		ASSERT_EQ("0.2", value);

		ASSERT_EQ("resource", root->getProperty<string>("name"));

		root->setProperty("name", "resource1")
			.setProperty("month", 2)
			.set("section2:version", "0.3");

		ASSERT_EQ("resource1", root->getProperty<string>("name"));
		ASSERT_EQ("0.3", root->getProperty<string>("section2:version"));

		ASSERT_EQ(2019, root->getProperty<int>("year"));
		ASSERT_EQ(2, root->getProperty<int>("month"));
	}

	TEST(ConfigurationRootTests, StringToValues) {

		ASSERT_EQ("test", convertTo<string>("test"));
		ASSERT_EQ("test and demo", convertTo<string>("test and demo"));
		ASSERT_EQ(10, convertTo<int>("10"));
	}
}
