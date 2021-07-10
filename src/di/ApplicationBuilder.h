#pragma once
#include "IApplicationBuilder.h"

namespace Matrix
{
	class ApplicationBuilder : public IApplicationBuilder
	{
	public:
		ApplicationBuilder();

		~ApplicationBuilder();

		virtual std::vector<std::shared_ptr<IComponent>>& getComponents() override;

		virtual std::vector<std::shared_ptr<IApplicationStartBlock>>& getBlocks() override;


	protected:
		virtual IApplicationBuilder& registerComponent(std::shared_ptr<IComponent> component) override;

		virtual IApplicationBuilder& registerStartBlock(std::shared_ptr<IApplicationStartBlock> block) override;

		
	private:
		std::vector<std::shared_ptr<IComponent>> mComponents;
		std::vector<std::shared_ptr<IApplicationStartBlock>> mBlocks;
	};


}