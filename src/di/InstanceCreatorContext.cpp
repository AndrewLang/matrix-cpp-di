#include "di/InstanceCreatorContext.h"
#include "di/IServiceProvider.h"

namespace Matrix
{
	InstanceCreatorContext::InstanceCreatorContext(IServiceProvider* provider, ParameterFactoryCreator<void>  resolver)
		: serviceProvider(provider)
		, factoryResolver(resolver) {}
}