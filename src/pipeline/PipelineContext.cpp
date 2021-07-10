#include "pipeline/PipelineContext.h"

namespace Matrix
{
	using std::shared_ptr;

	PipelineContext::PipelineContext()
	{

	}

	PipelineContext::PipelineContext(shared_ptr<IServiceProvider> serviceProvider)
		: DataContext(serviceProvider)
	{

	}

	void PipelineContext::abort()
	{
		mRequestAborted = true;
	}

	bool PipelineContext::isAborted() const
	{
		return mRequestAborted;
	}		
}