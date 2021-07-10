#include "pipeline/PipelineBuilder.h"
#include "pipeline/PipelineBlock.h"
#include "pipeline/Pipeline.h"

namespace Matrix
{
	using std::shared_ptr;
	using std::vector;

	PipelineBuilder::PipelineBuilder(shared_ptr<IServiceProvider> serviceProvider)
		:mServiceProvider(serviceProvider)
	{
	}

	PipelineBuilder::~PipelineBuilder()
	{
	}

	shared_ptr<IPipeline> PipelineBuilder::build()
	{
		auto factory = mServiceProvider->resolveService<ILoggerFactory>();
		return std::make_shared<Pipeline>(mBlocks, factory);		
	}

	IPipelineBuilder & PipelineBuilder::use(shared_ptr<IPipelineBlock> block)
	{
		mBlocks.push_back(block);

		return *this;
	}

	IPipelineBuilder & PipelineBuilder::use(std::function<void(PipelineContext&)> action, std::string name)
	{
		auto factory = mServiceProvider->resolveService<ILoggerFactory>();
		auto block = std::make_shared<PipelineBlock>(action, factory, name);
		use(block);

		return *this;
	}

	vector<shared_ptr<IPipelineBlock>> PipelineBuilder::getBlocks() const
	{
		return mBlocks;
	}
}