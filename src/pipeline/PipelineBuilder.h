#pragma once
#include "IPipelineBuilder.h"
#include "di/IServiceProvider.h"

#include <vector>


namespace Matrix
{
	class PipelineBuilder : public IPipelineBuilder
	{
	public:
		PipelineBuilder(std::shared_ptr<IServiceProvider> serviceProvider);

		~PipelineBuilder();

		virtual std::shared_ptr<IPipeline> build() override;

		virtual IPipelineBuilder& use(std::shared_ptr<IPipelineBlock> block) override;

		virtual IPipelineBuilder& use(std::function<void(PipelineContext&)> action, std::string name = "") override;

		std::vector<std::shared_ptr<IPipelineBlock>> getBlocks() const;
		
	private:
		std::vector<std::shared_ptr<IPipelineBlock>> mBlocks;

		std::shared_ptr<IServiceProvider> mServiceProvider;
	};

}