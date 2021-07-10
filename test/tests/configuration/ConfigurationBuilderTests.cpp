#include "gtest/gtest.h"
#include "configuration/ConfigurationBuilder.h"
#include "configuration/MemoryConfigurationProvider.h"

namespace Matrix
{
	TEST(ConfigurationBuilderTests, Constructor) {
		ConfigurationBuilder builder;
	}

	TEST(ConfigurationBuilderTests, AddProvider) {
		ConfigurationBuilder builder;
		builder.useProvider<MemoryConfigurationProvider>();

		auto providers = builder.getProviders();
		ASSERT_EQ(1, providers.size());
	}

	TEST(ConfigurationBuilderTests, Build) {
		ConfigurationBuilder builder;

		builder.useProvider<MemoryConfigurationProvider>();

		auto configuration = builder.build();
	}

}