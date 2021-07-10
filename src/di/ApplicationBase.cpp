#include "di/ApplicationBase.h"
#include "di/ServiceContainer.h"
#include "logging/LoggerFactory.h"
#include "logging/ILoggerFactory.h"
#include "logging/ConsoleLoggerProvider.h"
#include "logging/VsOutputLoggerProvider.h"
#include "configuration/ConfigurationBuilder.h"
#include "configuration/MemoryConfigurationProvider.h"
#include "pipeline/IPipelineBlock.h"

#include <algorithm>

namespace Matrix
{
	using std::shared_ptr;
	using std::vector;

	IApplication& ApplicationBase::initializeComponents()
	{
		/*
			call each component to configure service
		*/
		for (auto component : mComponents)
		{
			component->configureServices(mServiceContainer);
		}

		/*
			call each component to configure
		*/
		for (auto component : mComponents)
		{
			component->configure(mServiceContainer);
		}
		return *this;
	}

	IApplication& ApplicationBase::initializeServices()
	{
		auto container = std::make_shared<ServiceContainer>();

		auto configuration = initializeConfiguration();

		container->instance<IConfiguration>(configuration);

		container->singleton<ILoggerFactory, LoggerFactory>()
			.instance<IApplication>(shared_from_this());

		auto factory = container->resolveService<ILoggerFactory>();

		factory->useProvider<ConsoleLoggerProvider>()
			.useProvider<VsOutputLoggerProvider>();

		mServiceContainer = container;

		registerServices(mServiceContainer);

		return *this;
	}

	IApplication& ApplicationBase::start()
	{
		for (auto component : mComponents)
		{
			auto exe = std::dynamic_pointer_cast<IExecutableComponent>(component);
			if (exe)
			{
				exe->execute();
			}
		}


		std::sort(mBlocks.begin(), mBlocks.end(), PipelineBlockCompare());

		if (!mBlocks.empty())
		{
			ApplicationStartBlockContext context(getServiceContainer()) ;
			context.application = shared_from_this();
			context.serviceProvider = mServiceContainer;

			for (auto block : mBlocks)
			{
				block->process(context);

				if (context.isAborted())
				{
					break;
				}
			}
		}

		return *this;
	}

	IApplication& ApplicationBase::tearDown()
	{
		for (auto component : mComponents)
		{
			component->tearDown();
		}
		return *this;
	}

	IApplication& ApplicationBase::registerComponent(shared_ptr<IComponent> component)
	{
		mComponents.push_back(component);

		return *this;
	}

	IApplication & ApplicationBase::registerStartBlock(shared_ptr<IApplicationStartBlock> block)
	{
		mBlocks.push_back(block);

		return *this;
	}

	IApplication & ApplicationBase::registerStartBlocks(vector<shared_ptr<IApplicationStartBlock>> blocks)
	{
		for (auto &block : blocks)
		{
			mBlocks.push_back(block);
		}

		return *this;
	}

	shared_ptr<IConfiguration> ApplicationBase::initializeConfiguration()
	{
		vector<shared_ptr<IConfigurationProvider>> providers;

		ConfigurationBuilder builder;
		builder.useProvider<MemoryConfigurationProvider>();

		auto configuration = builder.build();
		return configuration;
	}

	std::shared_ptr<IServiceContainer> ApplicationBase::getServiceContainer()
	{
		return mServiceContainer;
	}

	vector<shared_ptr<IComponent>> ApplicationBase::getComponents()
	{
		return mComponents;
	}

	vector<shared_ptr<IApplicationStartBlock>> ApplicationBase::getBlocks() const
	{
		return mBlocks;
	}
	
	ApplicationBase::ApplicationBase()
	{
	}

	ApplicationBase::~ApplicationBase()
	{
	}
}