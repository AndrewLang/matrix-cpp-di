#include "di/ApplicationStartBlockContext.h"


namespace Matrix
{
	using std::shared_ptr;

	ApplicationStartBlockContext::ApplicationStartBlockContext()
	{

	}

	ApplicationStartBlockContext::ApplicationStartBlockContext(shared_ptr<IServiceProvider> serviceProvider)
		: PipelineContext(serviceProvider)
	{

	}

	ApplicationStartBlockContext::ApplicationStartBlockContext(PipelineContext & context)
	{
		copy(context);
	}
}

