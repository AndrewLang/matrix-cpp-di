#pragma once
#include "IPipelineBlock.h"
#include "logging/ILoggerFactory.h"
#include "logging/ILogger.h"

#include <functional>


namespace Matrix
{

	class PipelineBlock : public IPipelineBlock
	{
	public:
		PipelineBlock(std::function<void(PipelineContext&)>& action, std::shared_ptr<ILoggerFactory> loggerFactory, std::string blockName, int blockOrrder = 100);

		~PipelineBlock();

		virtual void process(PipelineContext & context) override;

	private:
		std::function<void(PipelineContext&)> mAction;
		std::shared_ptr<ILogger> mLogger;
	};
}

