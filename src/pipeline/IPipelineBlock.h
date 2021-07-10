#pragma once
#include "PipelineContext.h"

namespace Matrix
{
	class IPipelineBlock
	{
	public:
		std::string name;

		int order;

		virtual void process(PipelineContext & context) = 0;
	};


	struct PipelineBlockCompare
	{
		inline bool operator() (const std::shared_ptr<IPipelineBlock> block1, const std::shared_ptr<IPipelineBlock> block2)
		{
			return (block1->order < block2->order);
		}
	};
}