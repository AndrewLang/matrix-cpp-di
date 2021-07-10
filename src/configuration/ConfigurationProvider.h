#pragma once
#include "IConfigurationProvider.h"

#include <map>



namespace Matrix
{
	class ConfigurationProvider : public IConfigurationProvider
	{
	public:
		
		virtual void load() override;

		virtual void save(std::shared_ptr<IConfiguration> configuration) override;

		virtual bool tryGet(std::string key, std::string& value, std::string defaultValue = "") override;

		virtual IConfigurationProvider& set(std::string key, std::string value) override;

		virtual std::vector<std::string> getChildKeys(std::vector<std::string> earlierKeys, std::string parentPath, std::string delimiter) override;

	private:
		std::map<std::string, std::string> mInternalData;
	};

}