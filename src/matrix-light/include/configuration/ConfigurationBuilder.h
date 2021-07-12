#pragma once
#include "IConfigurationBuilder.h"

namespace Matrix
{

	class ConfigurationBuilder: public IConfigurationBuilder
	{
	public:
		ConfigurationBuilder();

		~ConfigurationBuilder();

		virtual IConfigurationBuilder& add(std::shared_ptr<IConfigurationProvider> provider) override;

		virtual std::shared_ptr<IConfigurationRoot> build() override;

		virtual std::vector<std::shared_ptr<IConfigurationProvider>> getProviders() override;

	private:
		std::vector<std::shared_ptr<IConfigurationProvider>> mProviders;
	};


}