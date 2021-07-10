#pragma once
#include "PipelineContext.h"
#include "IPipeline.h"
#include "IPipelineBlock.h"
#include "common/ObjectMap.h"

#include <functional>


namespace Matrix
{
	class IPipelineBuilder
	{
	public:
		virtual std::shared_ptr<IPipeline> build() = 0;

		virtual IPipelineBuilder& use(std::shared_ptr<IPipelineBlock> block) = 0;

		virtual IPipelineBuilder& use(std::function<void(PipelineContext&)> action, std::string name = "") = 0;

		template<typename TKey>
		IPipelineBuilder& useProperty(std::string name, TKey value)
		{
			mProperties.add<TKey>(name, value);
			return *this;
		}

	private:
		ObjectMap<std::string> mProperties;
	};
}