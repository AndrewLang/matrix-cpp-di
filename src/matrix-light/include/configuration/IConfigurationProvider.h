#pragma once
#include <memory>
#include <string>
#include <vector>


namespace Matrix
{
	class IConfiguration;

	class IConfigurationProvider
	{
	public:
		virtual void load() = 0;

		virtual void save(std::shared_ptr<IConfiguration> configuration) = 0;

		virtual bool tryGet(std::string key, std::string& value, std::string defaultValue = "") = 0;

		virtual IConfigurationProvider& set(std::string key, std::string value) = 0;

		virtual std::vector<std::string> getChildKeys(std::vector<std::string> earlierKeys, std::string parentPath, std::string delimiter) = 0;
	};
}