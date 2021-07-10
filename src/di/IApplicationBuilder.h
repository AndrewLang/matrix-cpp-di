#pragma once
#include "IApplication.h"

#include <memory>


namespace Matrix
{
	class IApplicationBuilder
	{
	public:
		template<class TKey, class... TArgs>
		std::shared_ptr<IApplication> build(TArgs&&... args)
		{
			auto app = std::make_shared<TKey>(args...);
			for (auto component : getComponents())
			{
				app->registerComponent(component);
			}

			for (auto block : getBlocks())
			{
				app->registerStartBlock(block);
			}
			return app;
		}
				
		template<class TKey>
		IApplicationBuilder& useComponent()
		{
			registerComponent(std::static_pointer_cast<IComponent>(std::make_shared<TKey>()));
			return *this;
		}

		template<class TKey, class... TArgs>
		IApplicationBuilder& useComponent(TArgs&&... args)
		{
			registerComponent(std::static_pointer_cast<IComponent>(std::make_shared<TKey>(args...)));
			return *this;
		}
		
		template<class TKey, class... TArgs>
		IApplicationBuilder& useBlock(TArgs&&... args)
		{
			registerStartBlock(std::make_shared<TKey>(args...));
			return *this;
		}

		virtual std::vector<std::shared_ptr<IComponent>>& getComponents() = 0;

		virtual std::vector<std::shared_ptr<IApplicationStartBlock>>& getBlocks() = 0;


	protected:
		virtual IApplicationBuilder& registerComponent(std::shared_ptr<IComponent> component) = 0;

		virtual IApplicationBuilder& registerStartBlock(std::shared_ptr<IApplicationStartBlock> block) = 0;			
	};
}