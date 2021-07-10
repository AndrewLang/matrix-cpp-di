#include "configuration/ConfigurationBuilder.h"
#include "configuration/ConfigurationRoot.h"

namespace Matrix
{
	using std::vector;
	using std::shared_ptr;

	ConfigurationBuilder::ConfigurationBuilder()
	{
	}

	ConfigurationBuilder::~ConfigurationBuilder()
	{
	}
	IConfigurationBuilder & ConfigurationBuilder::add(shared_ptr<IConfigurationProvider> provider)
	{
		if (provider)
		{
			mProviders.push_back(provider);
		}

		return *this;
	}
	shared_ptr<IConfigurationRoot> ConfigurationBuilder::build()
	{
		return std::make_shared<ConfigurationRoot>(mProviders);		
	}
	vector<shared_ptr<IConfigurationProvider>> ConfigurationBuilder::getProviders()
	{
		return mProviders;
	}
}