#pragma once
#include "di/IApplicationStartBlock.h"
#include "services/IAppStartBlockProvider.h"
#include "common/ObjectMap.h"

#include <memory>
#include <vector>

namespace Matrix
{
	class AppStartBlockProvider : public IAppStartBlockProvider
	{
	public:
		virtual IAppStartBlockProvider& initialize(std::shared_ptr<IServiceProvider> serviceProvider) override;

		virtual std::shared_ptr<IApplicationStartBlock> getBlock(const std::string& blockName) override;

		virtual std::vector<std::shared_ptr<IApplicationStartBlock>> getBlocks() override;

		virtual IAppStartBlockProvider& registerBlock(std::string blockName, std::shared_ptr<IApplicationStartBlock> block) override;

	private:
		ObjectMap<std::string> mBlocks;
	};
}