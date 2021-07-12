#pragma once
#include "di/IComponent.h"

namespace Matrix
{

	class InitializeComponent : public IComponent
	{
	public:
		InitializeComponent();

		~InitializeComponent();

		void configureServices(std::shared_ptr<IServiceContainer> serviceContainer) override;

		void configure(std::shared_ptr<IServiceProvider> serviceProvider) override;

		void tearDown() override;
	};

}

