#include "di/ComponentBase.h"

namespace Matrix
{
	using std::shared_ptr;

	void ComponentBase::configureServices(shared_ptr<IServiceContainer> serviceContainer)
	{
	}

	void ComponentBase::configure(shared_ptr<IServiceProvider> serviceProvider)
	{
	}

	void ComponentBase::tearDown()
	{
	}	
}