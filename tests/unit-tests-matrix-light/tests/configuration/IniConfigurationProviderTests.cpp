#include "gtest/gtest.h"
#include "configuration/IniConfigurationProvider.h"
#include "TestFiles.h"


namespace Matrix
{
	TEST(IniConfigurationProviderTests, Constructor) {
		IniConfigurationProvider provider;
	}

	TEST(IniConfigurationProviderTests, FilePath) {
		IniConfigurationProvider provider;
		provider.fullPath = "configuration.ini";

		ASSERT_EQ("configuration.ini", provider.fullPath);
	}

	TEST(IniConfigurationProviderTests, GetProperties) {
		IniConfigurationProvider provider;
		TestFiles files;

		provider.fullPath = files.getConfiguration();
		provider.load();

		ASSERT_EQ("Keysight Technologies", provider.getProperty<string>("ResourceManager", "Name"));
		ASSERT_EQ("Resource Manager", provider.getProperty<string>("ResourceManager", "Method"));

		ASSERT_EQ("Keysight Technologies", provider.getProperty<string>("TriggerManager","Vendor"));
		ASSERT_EQ("Resource Manager", provider.getProperty<string>("TriggerManager","Method"));

		ASSERT_EQ("Keysight Technologies", provider.getProperty<string>("ResourceManager:Name"));
		ASSERT_EQ("Resource Manager", provider.getProperty<string>("ResourceManager:Method"));

		ASSERT_EQ("Keysight Technologies", provider.getProperty<string>("TriggerManager:Vendor"));
		ASSERT_EQ("Resource Manager", provider.getProperty<string>("TriggerManager:Method"));
	}

	TEST(IniConfigurationProviderTests, GetPropertiesOfChassis) {
		IniConfigurationProvider provider;
		TestFiles files;

		provider.fullPath = files.get9030A();
		provider.load();

		ASSERT_EQ("Keysight Technologies", provider.getProperty<string>("Chassis:Vendor"));
		ASSERT_EQ("MS9030A", provider.getProperty<string>("Chassis:Model"));


		ASSERT_EQ(4, provider.getProperty<int>("StarTrigger1:SystemTimingSlot"));

		ASSERT_EQ(5, provider.getProperty<int>("StarSystemTimingSets1:SystemTimingSet9"));

		ASSERT_EQ("Slot2", provider.getProperty<string>("PXI1BusSegment1:IDSEL31"));
	}
	TEST(IniConfigurationProviderTests, FileExists) {
		/*TestFiles files;
		string configFile = files.getConfiguration();
		ASSERT_TRUE(OsFileSystem::isExisted(configFile));*/
	}

	TEST(IniConfigurationProviderTests, TestSimulateFile) {
		TestFiles files;
		IniConfigurationProvider provider;

		provider.fullPath = files.getSimulate();
		provider.load();

		ASSERT_EQ("MS9030A", provider.getProperty<string>("Chassis3:modelString"));
		ASSERT_EQ(60, provider.getProperty<int>("Chassis3:pciBusNumber1"));

		ASSERT_EQ("Keysight Test 8", provider.getProperty<string>("PxiDevice0:manufName"));
		ASSERT_EQ(27, provider.getProperty<int>("PxiDevice0:memSizeBar3"));
	}
}