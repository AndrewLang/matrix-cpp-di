#include "di/InstanceDescriptor.h"


namespace Matrix
{
	using namespace std;

	InstanceDescriptor::InstanceDescriptor()
	{
	}

	InstanceDescriptor::InstanceDescriptor(std::shared_ptr<TypeInfo> typeInfo, shared_ptr<void> instanceObj, string aliasName)
		: type(typeInfo), instance(instanceObj), alias(aliasName)
	{
	}
}
