#pragma once
#include "pipeline/IPipelineBlock.h"
#include "di/IServiceProvider.h"
#include "ApplicationStartBlockContext.h"

namespace Matrix
{
	class IApplicationStartBlock : public IPipelineBlock
	{
	public:
		virtual void process(ApplicationStartBlockContext & context) = 0;

		virtual std::shared_ptr<IApplicationStartBlock> withName(std::string blockName) = 0;

		virtual std::shared_ptr<IApplicationStartBlock> withOrder(int order) = 0;

		virtual std::shared_ptr<IApplicationStartBlock> withServices(std::shared_ptr<IServiceProvider> services) = 0;
	};
}