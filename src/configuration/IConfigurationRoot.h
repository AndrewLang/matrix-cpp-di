#pragma once
#include "IConfiguration.h"

namespace Matrix
{
	class IConfigurationRoot : public IConfiguration
	{
	public:
		virtual void reload() = 0;
	};
}