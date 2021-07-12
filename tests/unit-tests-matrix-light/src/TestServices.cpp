#include "TestServices.h"
#include "logging/ILoggerFactory.h"
#include "logging/LoggerFactory.h"
#include "logging/VsOutputLoggerProvider.h"

namespace Matrix
{
	TestServices::TestServices()
	{
	}
	
	TestServices::~TestServices()
	{
	}

	shared_ptr<IServiceProvider> TestServices::createServiceProvider()
	{
		auto serviceProvider = std::make_shared<ServiceContainer>();
		serviceProvider->singleton<ILoggerFactory, LoggerFactory>()			
			;


		auto loggerFactory = serviceProvider->resolveService<ILoggerFactory>();
		loggerFactory->useProvider<VsOutputLoggerProvider>();
		
		return serviceProvider;
	}
}