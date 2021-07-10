#pragma once
#include "di/IComponent.h"

namespace Matrix
{
	class ComponentBase : public IComponent
	{
	public:
		virtual void configureServices(std::shared_ptr<IServiceContainer> serviceContainer) override;

		virtual void configure(std::shared_ptr<IServiceProvider> serviceProvider) override;

		virtual void tearDown() override;
	private:

	};

}