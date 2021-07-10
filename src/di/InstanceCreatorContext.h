#pragma once
#include "ServiceLifetime.h"

namespace Matrix
{
	class IServiceProvider;

	class InstanceCreatorContext
	{
	public:
		IServiceProvider* serviceProvider;

		ParameterFactoryCreator<void> factoryResolver;

		InstanceCreatorContext(IServiceProvider* provider, ParameterFactoryCreator<void>  resolver);
	};
}