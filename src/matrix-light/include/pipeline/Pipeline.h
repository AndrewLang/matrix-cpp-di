#pragma once
#include "IPipeline.h"
#include "IPipelineBlock.h"
#include "logging/ILoggerFactory.h"
#include "logging/ILogger.h"

#include <vector>


namespace Matrix
{
	class Pipeline : public IPipeline
	{
	public:
		Pipeline(std::vector<std::shared_ptr<IPipelineBlock>> blocks, std::shared_ptr<ILoggerFactory> loggerFactory);

		virtual void process(PipelineContext& context) override;
	private:
		std::vector<std::shared_ptr<IPipelineBlock>> mBlocks;
		std::shared_ptr<ILogger> mLogger;
	};

}