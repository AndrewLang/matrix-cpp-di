#pragma once
#include "di/TypeInfo.h"
#include <memory>
#include <string>

namespace Matrix
{
	class InstanceDescriptor
	{
	public:
		InstanceDescriptor();

		InstanceDescriptor(std::shared_ptr<TypeInfo>instanceType, std::shared_ptr<void> instanceObj, std::string aliasName);

		std::shared_ptr<void> instance;

		std::shared_ptr<TypeInfo> type;

		std::string alias;
	};
}
