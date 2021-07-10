#include "gtest/gtest.h"
#include "pipeline/PipelineBlock.h"
#include "logging/LoggerFactory.h"
#include "pipeline/PipelineContext.h"

namespace Matrix
{
	using std::function;
	TEST(PipelineBlockTests, Constructor) {
		function<void(PipelineContext&)> action = [](PipelineContext& context) {};

		auto loggerFactory = std::make_shared<LoggerFactory>();

		PipelineBlock block(action, loggerFactory, "test");

		ASSERT_EQ("test", block.name);
	}

	TEST(PipelineBlockTests, Process) {
		bool actionInvoked = false;

		function<void(PipelineContext&)> action = [&](PipelineContext& context) {
			actionInvoked = true;
			context.setProperty<bool>("started", true);
		};

		auto loggerFactory = std::make_shared<LoggerFactory>();

		PipelineBlock block(action, loggerFactory, "test");

		PipelineContext context;
		context.setProperty<bool>("started", false);
		block.process(context);

		ASSERT_TRUE(actionInvoked);
		ASSERT_TRUE(context.getProperty<bool>("started"));
	}
}