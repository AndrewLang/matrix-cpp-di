#include "pipeline/PipelineBlock.h"

namespace Matrix
{
	using std::string;
	using std::shared_ptr;
	using std::function;


	PipelineBlock::PipelineBlock(function<void(PipelineContext&)>& action, shared_ptr<ILoggerFactory> loggerFactory, string blockName, int blockOrrder)
		: mAction(action)
	{
		name = blockName;
		order = blockOrrder;
		mLogger = loggerFactory->createLogger("PipelineBlock " + blockName);
	}

	PipelineBlock::~PipelineBlock()
	{
	}

	void PipelineBlock::process(PipelineContext & context)
	{
		if (mAction)
		{
			try
			{
				mLogger->debug("Invoking block: ", name);

				mAction(context);
			}
			catch (const std::exception & e)
			{
				context.abort();

				mLogger->debug("Invoking block '", name, "' with exception: ", e.what());
			}			
		}
	}
}
