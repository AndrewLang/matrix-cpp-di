#pragma once
#include "IConfigurationRoot.h"
#include "IConfigurationProvider.h"
#include "IConfigurationSaver.h"

namespace Matrix
{
	class ConfigurationRoot : public IConfigurationRoot
		, public IConfigurationSaver
		, public std::enable_shared_from_this<ConfigurationRoot>
	{
	public:
		ConfigurationRoot(std::vector<std::shared_ptr<IConfigurationProvider>> providers);

		~ConfigurationRoot();

		void reload() override;

		void save() override;

		bool tryGet(std::string key, std::string& value, std::string defaultValue = "") override;

		IConfiguration& set(std::string key, std::string value) override;

	private:
		std::vector<std::shared_ptr<IConfigurationProvider>> mProviders;
	};

}