#include "di/ApplicationBuilder.h"

namespace Matrix
{
	using std::shared_ptr;
	using std::vector;

	ApplicationBuilder::ApplicationBuilder()
	{
	}
	
	ApplicationBuilder::~ApplicationBuilder()
	{
	}
	

	IApplicationBuilder & ApplicationBuilder::registerComponent(shared_ptr<IComponent> component)
	{
		mComponents.push_back(component);
		return *this;
	}

	IApplicationBuilder & ApplicationBuilder::registerStartBlock(shared_ptr<IApplicationStartBlock> block)
	{
		mBlocks.push_back(block);

		return *this;
	}

	vector<shared_ptr<IComponent>>& ApplicationBuilder::getComponents()
	{
		return mComponents;
	}

	vector<shared_ptr<IApplicationStartBlock>>& ApplicationBuilder::getBlocks()
	{
		return mBlocks;
	}

}
