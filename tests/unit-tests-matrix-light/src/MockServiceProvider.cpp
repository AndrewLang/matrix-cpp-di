#include "MockServiceProvider.h"

namespace Matrix
{
	std::shared_ptr<void> MockServiceprovider::getService(const std::shared_ptr<TypeInfo> typeInfo, const std::string name)
	{
		return std::shared_ptr<void>();
	}

}