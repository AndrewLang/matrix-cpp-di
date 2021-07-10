#pragma once
#include "di/ServiceContainer.h"
#include "di/IServiceContainer.h"
#include "di/IServiceProvider.h"

#include "logging/LoggerFactory.h"

#include <memory>

using std::shared_ptr;

namespace Matrix
{
	class TestServices
	{
	public:
		TestServices();
		~TestServices();

		static shared_ptr<IServiceProvider> createServiceProvider();
	};

}