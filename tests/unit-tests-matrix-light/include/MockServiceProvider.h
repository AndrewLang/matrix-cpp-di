#pragma once
#include "di/IServiceProvider.h"

namespace Matrix
{
	class MockServiceprovider : public IServiceProvider
	{
	public:
		std::shared_ptr<void> getService(const std::shared_ptr<TypeInfo> typeInfo,  std::string name = std::string()) override;
	};
}
