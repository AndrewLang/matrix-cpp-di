#include "gtest/gtest.h"
#include "pipeline/Pipeline.h"
#include "pipeline/PipelineBlock.h"
#include "logging/LoggerFactory.h"


namespace Matrix
{
	using std::string;
	using std::function;
	using std::vector;
	using std::shared_ptr;
	TEST(PipelineTests, Constructor) {
		vector<shared_ptr<IPipelineBlock>> blocks;
		auto loggerFactory = std::make_shared<LoggerFactory>();

		Pipeline pipeline(blocks, loggerFactory);
	}

	TEST(PipelineTests, Process) {
		auto loggerFactory = std::make_shared<LoggerFactory>();

		bool actionInvoked = false;

		function<void(PipelineContext&)> action = [&](PipelineContext& context) {
			actionInvoked = true;
			context.setProperty<bool>("started", true);
		};

		vector<shared_ptr<IPipelineBlock>> blocks;
		blocks.push_back(std::make_shared<PipelineBlock>(action, loggerFactory, "test"));


		Pipeline pipeline(blocks, loggerFactory);

		PipelineContext context;
		context.setProperty<bool>("started", false);

		pipeline.process(context);

		ASSERT_TRUE(actionInvoked);
		ASSERT_TRUE(context.getProperty<bool>("started"));
	}

	TEST(PipelineTests, SortBlocks) {
		vector<shared_ptr<IPipelineBlock>> mBlocks;
		auto loggerFactory = std::make_shared<LoggerFactory>();

		function<void(PipelineContext&)> action = [&](PipelineContext& context) {			
			context.setProperty<bool>("started", true);
		};

		mBlocks.push_back(std::make_shared<PipelineBlock>(action, loggerFactory, "fifth", 500));
		mBlocks.push_back(std::make_shared<PipelineBlock>(action, loggerFactory, "fourth", 400));
		mBlocks.push_back(std::make_shared<PipelineBlock>(action, loggerFactory, "second", 200));
		mBlocks.push_back(std::make_shared<PipelineBlock>(action, loggerFactory, "third", 300));
		mBlocks.push_back(std::make_shared<PipelineBlock>(action, loggerFactory, "first", 100));

		std::sort(mBlocks.begin(), mBlocks.end(), PipelineBlockCompare());

		ASSERT_EQ(mBlocks[0]->name, "first");
		ASSERT_EQ(mBlocks[1]->name, "second");
		ASSERT_EQ(mBlocks[2]->name, "third");
		ASSERT_EQ(mBlocks[3]->name, "fourth");
		ASSERT_EQ(mBlocks[4]->name, "fifth");
	}
}