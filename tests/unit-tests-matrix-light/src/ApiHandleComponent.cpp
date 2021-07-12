#include "ApiHandleComponent.h"
#include "ApiHandler.h"
#include "di/IApplication.h"
#include "di/ApplicationStartBlock.h"
#include "logging/VsOutput.h"

namespace Matrix
{

	ApiHandleComponent::ApiHandleComponent()
	{
	}
	
	ApiHandleComponent::~ApiHandleComponent()
	{
	}

	void ApiHandleComponent::configureServices(std::shared_ptr<IServiceContainer> serviceContainer)
	{
		serviceContainer->singleton<IApiHandler, ApiHandler>();
	}

	void ApiHandleComponent::configure(std::shared_ptr<IServiceProvider> serviceProvider)
	{
		auto app = serviceProvider->resolveService<IApplication>();
		auto factory = serviceProvider->resolveService<ILoggerFactory>();

		AppStartAction action = [](ApplicationStartBlockContext& context) {
			VsOutput::writeWithName("ApiHandleBlock", "log messages from api handle block");
		};		

		auto block = std::make_shared<ApplicationStartBlock>(action, factory, "ApiHandle", 100);

		app->registerStartBlock(block);
	}

	void ApiHandleComponent::tearDown()
	{
	}

}
