#pragma once

#include "ConfigurationProvider.h"

namespace Matrix
{
	class MemoryConfigurationProvider : public ConfigurationProvider
	{
	public:
		MemoryConfigurationProvider();

		~MemoryConfigurationProvider();
	};
}