#include "gtest/gtest.h"
#include "di/ApplicationBase.h"
#include "di/IApplication.h"
#include "MockApplication.h"
#include "logging/ILoggerFactory.h"
#include "ApiHandleComponent.h"
#include "InitializeComponent.h"
#include "IApiHandler.h"
#include "di/ApplicationStartBlock.h"
#include "logging/LoggerFactory.h"



namespace Matrix
{
	using Connectivity::ILoggerFactory;
	using std::string;
	using std::function;
	using std::vector;
	using std::shared_ptr;

	TEST(ApplicationTests, Constructor) {
		MockApplication app;
	}

	TEST(ApplicationTests, InitializeServiceTest) {
		auto app = std::make_shared<MockApplication>();

		app->initializeServices();

		auto container = app->getServiceContainer();

		auto loggerFactory = container->resolveService<ILoggerFactory>();

		ASSERT_NE(nullptr, loggerFactory);

		auto configuration = container->resolveService<IConfiguration>();

		ASSERT_NE(nullptr, configuration);
	}

	TEST(ApplicationTests, UseComponent) {
		MockApplication app;

		app.useComponent<ApiHandleComponent>()
			.useComponent<InitializeComponent>();

		auto components = app.getComponents();

		ASSERT_EQ(2, components.size());
	}

	TEST(ApplicationTests, InitializeComponents) {
		auto app = std::make_shared<MockApplication>();

		app->useComponent<ApiHandleComponent>()
			.useComponent<InitializeComponent>();

		app->initializeServices()
			.initializeComponents();

		auto container = app->getServiceContainer();

		auto apiHandler = container->resolveService<IApiHandler>();

		ASSERT_NE(nullptr, apiHandler);
	}

	TEST(ApplicationTests, StartUp) {
		MockApplication app;

		app.useComponent<ApiHandleComponent>()
			.useComponent<InitializeComponent>();

		app.start();
	}

	TEST(ApplicationTests, TearDown) {
		MockApplication app;

		app.useComponent<ApiHandleComponent>()
			.useComponent<InitializeComponent>();

		app.start();

		app.tearDown();
	}

	TEST(ApplicationTests, RegisterBlocks) {
		auto app = std::make_shared<MockApplication>();

		auto factory = std::make_shared<LoggerFactory>();

		AppStartAction action = [](ApplicationStartBlockContext& context) {};

		auto block1 = std::make_shared<ApplicationStartBlock>(action, factory, "block1", 100);
		auto block2 = std::make_shared<ApplicationStartBlock>(action, factory, "block2", 500);

		(*app).registerStartBlock(block1)
			.registerStartBlock(block2);

		auto blocks = app->getBlocks();

		ASSERT_EQ(2, blocks.size());

		app->start();

		app->tearDown();
	}

	TEST(ApplicationTests, BatchRegisterBlocks) {
		auto app = std::make_shared<MockApplication>();

		auto factory = std::make_shared<LoggerFactory>();

		AppStartAction action = [](ApplicationStartBlockContext& context) {};

		auto block1 = std::make_shared<ApplicationStartBlock>(action, factory, "block1", 100);
		auto block2 = std::make_shared<ApplicationStartBlock>(action, factory, "block2", 500);

		vector<shared_ptr<IApplicationStartBlock>> startBlocks = {block1, block2};

		app->registerStartBlocks(startBlocks);

		auto blocks = app->getBlocks();

		ASSERT_EQ(2, blocks.size());

		app->start();

		app->tearDown();
	}

	TEST(ApplicationTests, RunBlocks) {
		auto app = std::make_shared<MockApplication>();

		auto factory = std::make_shared<LoggerFactory>();

		bool action1Invoked = false;
		bool action2Invoked = false;

		AppStartAction action1 = [&](ApplicationStartBlockContext& context) {
			action1Invoked = true;
			context.setProperty<string>("version", "1.0");
		};

		AppStartAction action2 = [&](ApplicationStartBlockContext& context) {
			action2Invoked = true;
			context.setProperty<string>("cli-version", "1.1");
		};

		auto block1 = std::make_shared<ApplicationStartBlock>(action1, factory, "block1", 100);
		auto block2 = std::make_shared<ApplicationStartBlock>(action2, factory, "block2", 500);

		(*app).registerStartBlock(block1)
			.registerStartBlock(block2);

		auto blocks = app->getBlocks();


		app->start();

		ASSERT_EQ(2, blocks.size());
		ASSERT_TRUE(action1Invoked);
		ASSERT_TRUE(action2Invoked);

		app->tearDown();
	}

	TEST(ApplicationTests, Demo) {
		auto app = std::make_shared<MockApplication>();

		app->useComponent<ApiHandleComponent>()
			.useComponent<InitializeComponent>()
			.initializeServices()
			.initializeComponents();

		app->start();

		app->tearDown();
	}
}