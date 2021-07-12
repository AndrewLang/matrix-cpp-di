#include "gtest/gtest.h"
#include "di/ApplicationStartBlock.h"
#include "di/ApplicationStartBlockContext.h"
#include "di/ServiceContainer.h"
#include "logging/LoggerFactory.h"

#include<functional>

using namespace std;

namespace Matrix
{
	TEST(ApplicationStartBlockTests, Constructor) {
		AppStartAction action = [](ApplicationStartBlockContext& context) {};
		auto loggerFactory = std::make_shared<LoggerFactory>();
		ApplicationStartBlock block(action, loggerFactory, "test", 20);
	}

	TEST(ApplicationStartBlockTests, ActionInvokedWithAppContext) {
		bool invoked = false;
		AppStartAction action = [&](ApplicationStartBlockContext& context) {
			invoked = true;
		};
		auto loggerFactory = std::make_shared<LoggerFactory>();
		ApplicationStartBlock block(action, loggerFactory, "test", 20);

		ApplicationStartBlockContext context;

		block.process(context);

		ASSERT_TRUE(invoked);
	}

	TEST(ApplicationStartBlockTests, ActionInvoked) {
		bool invoked = false;
		AppStartAction action = [&](ApplicationStartBlockContext& context) {
			invoked = true;
		};
		auto loggerFactory = std::make_shared<LoggerFactory>();
		ApplicationStartBlock block(action, loggerFactory, "test", 20);

		PipelineContext context;

		block.process(context);

		ASSERT_TRUE(invoked);
	}

	TEST(ApplicationStartBlockTests, WithName) {
		AppStartAction action = [](ApplicationStartBlockContext& context) {};

		auto block = std::make_shared<ApplicationStartBlock>(action)->withName("test");

		ASSERT_EQ(block->name, "test");
	}

	TEST(ApplicationStartBlockTests, WithOrder) {
		AppStartAction action = [](ApplicationStartBlockContext& context) {};
		auto block = std::make_shared<ApplicationStartBlock>(action)->withOrder(99);
		
		ASSERT_EQ(block->order, 99);
	}

	TEST(ApplicationStartBlockTests, WithServices) {
		auto container = std::make_shared<ServiceContainer>();
		
		container->singleton<ILoggerFactory, LoggerFactory>();

		AppStartAction action = [](ApplicationStartBlockContext& context) {};
		auto block = std::make_shared<ApplicationStartBlock>(action)->withServices(container);
	}
}