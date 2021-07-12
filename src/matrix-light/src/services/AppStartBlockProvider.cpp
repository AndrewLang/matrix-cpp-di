#include "di/ApplicationStartBlock.h"
#include "services/AppStartBlockProvider.h"


namespace Matrix
{
	using std::shared_ptr;
	using std::string;
	using std::vector;

	IAppStartBlockProvider& AppStartBlockProvider::initialize(shared_ptr<IServiceProvider> serviceProvider)
	{		
		return *this;
	}

	shared_ptr<IApplicationStartBlock> AppStartBlockProvider::getBlock(const string& blockName)
	{
		if (mBlocks.contains(blockName))
		{
			return mBlocks.getValue<shared_ptr<IApplicationStartBlock>>(blockName);
		}
		return nullptr;
	}

	vector<shared_ptr<IApplicationStartBlock>> AppStartBlockProvider::getBlocks()
	{
		vector<shared_ptr<IApplicationStartBlock>> result;

		for (auto &item : mBlocks.keys())
		{
			result.push_back(mBlocks.getValue<shared_ptr<IApplicationStartBlock>>(item));
		}

		return result;		
	}

	IAppStartBlockProvider & AppStartBlockProvider::registerBlock(std::string blockName, std::shared_ptr<IApplicationStartBlock> block)
	{
		mBlocks.add(blockName, block);

		return *this;
	}
}