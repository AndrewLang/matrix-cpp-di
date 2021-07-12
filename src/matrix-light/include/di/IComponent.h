#pragma once
#include "IServiceContainer.h"
#include "IServiceProvider.h"

#include <memory>


namespace Matrix
{
	class IComponent
	{
	public:
		virtual void configureServices(std::shared_ptr<IServiceContainer> serviceContainer) = 0;

		virtual void configure(std::shared_ptr<IServiceProvider> serviceProvider) = 0;

		virtual void tearDown() = 0;
	};

	class IExecutableComponent : public IComponent
	{
	public:
		virtual void execute() = 0;
	};
}