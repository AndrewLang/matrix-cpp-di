#include "configuration/ConfigurationRoot.h"

#include <vector>
#include <set>



namespace Matrix
{
	using std::vector;
	using std::shared_ptr;
	using std::string;
	using std::set;

	ConfigurationRoot::ConfigurationRoot(vector<shared_ptr<IConfigurationProvider>> providers)
		: mProviders(providers)
	{
	}

	ConfigurationRoot::~ConfigurationRoot()
	{
	}

	void ConfigurationRoot::reload()
	{
		for (auto provider : mProviders)
		{
			provider->load();
		}
	}

	void ConfigurationRoot::save()
	{
		for (auto provider : mProviders)
		{
			provider->save(shared_from_this());
		}
	}
	bool ConfigurationRoot::tryGet(string key, string & value, string defaultValue)
	{
		for (auto provider : mProviders)
		{
			if (provider->tryGet(key, value, defaultValue))
			{
				return true;
			}
		}

		return false;
	}
	IConfiguration & ConfigurationRoot::set(string key, string value)
	{
		for (auto provider : mProviders)
		{
			provider->set(key, value);
		}

		return *this;
	}
}