#pragma once
#include "PipelineContext.h"

namespace Matrix
{
	class IPipeline
	{
	public:
		virtual void process(PipelineContext& context) = 0;
	};
}