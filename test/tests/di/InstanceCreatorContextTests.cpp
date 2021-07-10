#include "gtest/gtest.h"
#include "di/InstanceCreatorContext.h"
#include "MockServiceContainer.h"
#include "Rectangle.h"
#include "di/IServiceProvider.h"
#include "di/IServiceContainer.h"

namespace Matrix
{
	TEST(InstanceCreatorContextTests, Constructor) {
		auto provider = new MockServiceprovider();

		ParameterFactoryCreator<Rectangle> factoryResolver = [](IServiceProvider* serviceProvider) {
			return ParameterInstanceFactory<Rectangle>("DEFAULT", 20, 30);
		};

		InstanceCreatorContext context(provider, factoryResolver);

		delete provider;
		provider = NULL;
	}

}
