#pragma once
#include "di/IServiceContainer.h"
#include "di/IServiceProvider.h"
#include "MockServiceProvider.h"

namespace Matrix
{
	class MockServiceContainer: public IServiceContainer
	{
	public:
		std::shared_ptr<void> getService(const std::shared_ptr<TypeInfo> typeInfo, std::string name = std::string()) override;

		IServiceContainer & registerService(std::shared_ptr<ServiceDescriptor> descriptor) override;

	private:
		std::vector<ServiceDescriptor*> mDescriptors;
	};

}