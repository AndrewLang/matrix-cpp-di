#pragma once
#include "IApplication.h"
#include "IComponent.h"

#include <memory>


namespace Matrix
{
	class ApplicationBase : public IApplication, public std::enable_shared_from_this<ApplicationBase>
	{
	public:
		std::shared_ptr<IConfiguration> initializeConfiguration() override;

		IApplication& initializeComponents() override;

		IApplication& initializeServices() override;

		IApplication& start() override;

		IApplication& tearDown() override;

		IApplication& registerComponent(std::shared_ptr<IComponent> component) override;

		IApplication& registerStartBlock(std::shared_ptr<IApplicationStartBlock> block) override;

		virtual IApplication& registerStartBlocks(std::vector<std::shared_ptr<IApplicationStartBlock>> blocks) override;

		std::shared_ptr<IServiceContainer> getServiceContainer() override;

		std::vector<std::shared_ptr<IComponent>> getComponents() override;
		
		std::vector<std::shared_ptr<IApplicationStartBlock>> getBlocks() const;
				
		ApplicationBase();

		~ApplicationBase();

	private:
		std::vector<std::shared_ptr<IComponent>> mComponents;
		std::vector<std::shared_ptr<IApplicationStartBlock>> mBlocks;
		std::shared_ptr<IServiceContainer> mServiceContainer;

	protected:
		virtual void registerServices(std::shared_ptr<IServiceContainer> container) = 0;

	};

}
