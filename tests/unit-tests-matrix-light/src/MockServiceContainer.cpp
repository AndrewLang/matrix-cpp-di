#include "MockServiceContainer.h"

namespace Matrix
{
	std::shared_ptr<void> MockServiceContainer::getService(const std::shared_ptr<TypeInfo> typeInfo, const std::string name)
	{
		return std::shared_ptr<void>();
	}
	IServiceContainer & MockServiceContainer::registerService(std::shared_ptr<ServiceDescriptor> descriptor)
	{
		return *this;
	}
}