#include "di/ServiceContainer.h"
#include "common/VectorExtensions.h"

namespace Matrix
{
	using namespace std;


	ServiceContainer::ServiceContainer() {}

	ServiceContainer::ServiceContainer(ServiceContainer && container) { }

	ServiceContainer::~ServiceContainer() { }

	std::shared_ptr<void> ServiceContainer::getService(const shared_ptr<TypeInfo> typeInfo, const string name)
	{
		return resolveInstance<void>(typeInfo, name);
	}

	IServiceContainer & ServiceContainer::registerService(shared_ptr<ServiceDescriptor> descriptor)
	{
		mDescriptors.push_back(descriptor);

		return *this;
	}

	shared_ptr<ServiceDescriptor> ServiceContainer::findDescriptor(string typeName, string instanceName)
	{
		shared_ptr<ServiceDescriptor> result = nullptr;
		for (auto descriptor : mDescriptors)
		{
			if ((Strings::isNullOrEmpty(instanceName) && descriptor->serviceType->name == typeName) ||
				(!Strings::isNullOrEmpty(instanceName) && descriptor->serviceType->name == typeName && descriptor->alias == instanceName)
				)
			{
				result = descriptor;
				break;
			}
		}

		return result;
	}

	shared_ptr<InstanceDescriptor> ServiceContainer::findInstance(const shared_ptr<TypeInfo> type, string instanceName)
	{
		return Vectors::firstOrDefault<shared_ptr<InstanceDescriptor>>(mInstances, [=](shared_ptr<InstanceDescriptor> descriptor) {

			return
				Strings::isNullOrEmpty(instanceName) ?
				descriptor->type->name == type->name :
				descriptor->type->name == type->name  && descriptor->alias == instanceName;

			});
	}
}