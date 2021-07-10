#pragma once
#include "../pipeline/PipelineContext.h"
#include "IServiceProvider.h"


namespace Matrix
{
	class IApplication;
	
	class ApplicationStartBlockContext : public PipelineContext
	{
	public:
		ApplicationStartBlockContext();

		ApplicationStartBlockContext(std::shared_ptr<IServiceProvider> serviceProvider);

		ApplicationStartBlockContext(PipelineContext& context);

		std::shared_ptr<IApplication> application;

		std::shared_ptr<IServiceProvider> serviceProvider;
	};
}