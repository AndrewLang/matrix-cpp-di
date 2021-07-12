#include "configuration/ConfigurationProvider.h"
#include "common/StringExtensions.h"

namespace Matrix
{
	using std::shared_ptr;
	using std::string;
	using std::vector;

	void ConfigurationProvider::load()
	{
	}

	void ConfigurationProvider::save(shared_ptr<IConfiguration> configuration)
	{
	}

	bool ConfigurationProvider::tryGet(string key, string& value, string defaultValue)
	{
		auto iterator = mInternalData.find(key);
		if (iterator != mInternalData.end())
		{
			value = iterator->second;
			return true;
		}
		else
		{
			value = defaultValue;
			return false;
		}
	}

	IConfigurationProvider & ConfigurationProvider::set(string key, string value)
	{
		mInternalData[key] = value;

		return *this;
	}

	vector<string> ConfigurationProvider::getChildKeys(vector<string> earlierKeys, string parentPath, string delimiter)
	{
		vector<string> vectors;
		vectors.insert(vectors.end(), earlierKeys.begin(), earlierKeys.end());

		string prefix = parentPath == "" ? "" : parentPath + delimiter;
		for (auto value : mInternalData)
		{
			if (StringExtensions::startsWith(value.first, prefix))
			{
				int index = static_cast<int>(value.first.find_first_of(delimiter, prefix.size()));
				if (index < 0)
				{
					vectors.push_back(value.first.substr(prefix.size()));
				}
				else
				{
					vectors.push_back(value.first.substr(prefix.size(), index - prefix.size()));
				}
			}
		}

		return vectors;
	}
}