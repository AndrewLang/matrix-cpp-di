#pragma once
#include "IComponent.h"
#include "../configuration/IConfiguration.h"
#include "IApplicationStartBlock.h"

#include <memory>


namespace Matrix
{
	class IApplication
	{
	public:
		virtual std::shared_ptr<IConfiguration> initializeConfiguration() = 0;

		virtual IApplication& initializeComponents() = 0;

		virtual IApplication& initializeServices() = 0;

		virtual IApplication& start() = 0;

		virtual IApplication& tearDown() = 0;

		virtual IApplication& registerComponent(std::shared_ptr<IComponent> component) = 0;

		virtual IApplication& registerStartBlock(std::shared_ptr<IApplicationStartBlock> block) = 0;

		virtual IApplication& registerStartBlocks(std::vector<std::shared_ptr<IApplicationStartBlock>> blocks) = 0;

		virtual std::shared_ptr<IServiceContainer> getServiceContainer() = 0;

		virtual std::vector<std::shared_ptr<IComponent>> getComponents() = 0;

		template<class TKey>
		IApplication& useComponent()
		{
			registerComponent(std::static_pointer_cast<IComponent>(std::make_shared<TKey>()));
			return *this;
		}

		template<class TKey, class... TArgs>
		IApplication& useComponent(TArgs&&... args)
		{
			registerComponent(std::static_pointer_cast<IComponent>(std::make_shared<TKey>(args...)));
			return *this;
		}
	};
}