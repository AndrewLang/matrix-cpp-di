#include "di/ServiceDescriptor.h"

namespace Matrix
{
	using namespace std;

	ServiceDescriptor::~ServiceDescriptor()
	{
		
	}


	ServiceDescriptor& ServiceDescriptor::withAlias(const string serviceAlias)
	{
		alias = serviceAlias;
		return *this;
	}
}
