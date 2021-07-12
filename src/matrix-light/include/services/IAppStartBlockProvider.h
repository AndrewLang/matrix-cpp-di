#pragma once
#include "di/IApplicationStartBlock.h"
#include <memory>
#include <vector>

namespace Matrix
{
	class IAppStartBlockProvider
	{
	public:
		virtual IAppStartBlockProvider& initialize(std::shared_ptr<IServiceProvider> serviceProvider) = 0;

		virtual std::shared_ptr<IApplicationStartBlock> getBlock(const std::string& blockName) = 0;

		virtual std::vector<std::shared_ptr<IApplicationStartBlock>> getBlocks() = 0;

		virtual IAppStartBlockProvider& registerBlock(std::string blockName, std::shared_ptr<IApplicationStartBlock> block) = 0;
	
	private:

	};
}