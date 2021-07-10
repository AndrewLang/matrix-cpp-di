#include "TestServices.h"
#include "logging/ILoggerFactory.h"
#include "logging/LoggerFactory.h"
#include "logging/VsOutputLoggerProvider.h"
#include "services/IEnvironmentProfile.h"
#include "services/IFileLocker.h"
#include "services/IPxiInfoTreeLoader.h"
#include "models/PxiKeys.h"

#include "TestRuntimeProfile.h"
#include "MockPeripheralModuleRegistryLoader.h"
#include "MockPxiChassisRegistryLoader.h"
#include "MockSystemModuleRegistryLoader.h"

#include "platformCheckMacros.h"

#if defined(_WIN32)
#include "windows/WinFileLocker.h"
#endif

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
			.singleton<IEnvironmentProfile, TestRuntimeProfile>()
			.singleton<IPxiInfoTreeLoader, MockPeripheralModuleRegistryLoader>(PxiKeys::PeripheralModuleInfoLoaderKey)
			.singleton<IPxiInfoTreeLoader, MockPxiChassisRegistryLoader>(PxiKeys::PxiChassisInfoLoaderKey)
			.singleton<IPxiInfoTreeLoader, MockSystemModuleRegistryLoader>(PxiKeys::PxiSystemModuleInfoLoaderKey)
			;

#if defined(_WIN32)
		serviceProvider->singleton<IFileLocker, WinFileLocker>();
#else 

#endif
		auto loggerFactory = serviceProvider->resolveService<ILoggerFactory>();
		loggerFactory->useProvider<VsOutputLoggerProvider>();
		
		return serviceProvider;
	}
}