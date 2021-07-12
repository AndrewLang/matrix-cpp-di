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

    TEST(IniConfigurationProviderTests, DISABLED_GetProperties) {
        IniConfigurationProvider provider;
        TestFiles files;

        provider.fullPath = files.getConfiguration();
        provider.load();

        ASSERT_EQ("Jasoon", provider.getProperty<string>("Something", "Name"));
        ASSERT_EQ("Spaceship", provider.getProperty<string>("Something", "Method"));

        ASSERT_EQ("Jasoon", provider.getProperty<string>("Something:Name"));
        ASSERT_EQ("Spaceship", provider.getProperty<string>("Something:Method"));

    }
}