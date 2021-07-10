#include "gtest/gtest.h"
#include "pipeline/PipelineBuilder.h"
#include "di/ServiceContainer.h"
#include "logging/ILoggerFactory.h"
#include "logging/LoggerFactory.h"
#include "pipeline/PipelineBlock.h"
#include "pipeline/PipelineContext.h"

namespace Matrix
{
	using std::string;
	using std::function;

	TEST(PipelineBuilderTests, Constructor) {
		auto serviceContainer = std::make_shared<ServiceContainer>();
		serviceContainer->singleton<ILoggerFactory, LoggerFactory>();

		PipelineBuilder builder(serviceContainer);
	}


	TEST(PipelineBuilderTests, UseBlock) {
		auto serviceContainer = std::make_shared<ServiceContainer>();
		serviceContainer->singleton<ILoggerFactory, LoggerFactory>();


		PipelineBuilder builder(serviceContainer);

		bool actionInvoked = false;

		function<void(PipelineContext&)> action = [&](PipelineContext& context) {
			actionInvoked = true;
			context.setProperty<bool>("started", true);
		};

		auto  block = std::make_shared<PipelineBlock>(action, serviceContainer->resolveService<ILoggerFactory>(), "test");
		builder.use(block);

		ASSERT_EQ(1, builder.getBlocks().size());
	}

	TEST(PipelineBuilderTests, UseFunction) {
		auto serviceContainer = std::make_shared<ServiceContainer>();
		serviceContainer->singleton<ILoggerFactory, LoggerFactory>();


		PipelineBuilder builder(serviceContainer);

		bool actionInvoked = false;

		function<void(PipelineContext&)> action = [&](PipelineContext& context) {
			actionInvoked = true;
			context.setProperty<bool>("started", true);
		};

		builder.use(action, "test");;

		ASSERT_EQ(1, builder.getBlocks().size());
	}

	TEST(PipelineBuilderTests, Build) {
		auto serviceContainer = std::make_shared<ServiceContainer>();
		serviceContainer->singleton<ILoggerFactory, LoggerFactory>();


		PipelineBuilder builder(serviceContainer);

		bool actionInvoked = false;

		function<void(PipelineContext&)> action = [&](PipelineContext& context) {
			actionInvoked = true;
			context.setProperty<bool>("started", true);
		};

		function<void(PipelineContext&)> action2 = [&](PipelineContext& context) {
			context.setProperty<bool>("action2", true);
		};

		auto  block = std::make_shared<PipelineBlock>(action, serviceContainer->resolveService<ILoggerFactory>(), "test");

		builder.use(block)
			.use(action2, "action2");;

		ASSERT_EQ(2, builder.getBlocks().size());

		auto pipeline = builder.build();
		PipelineContext context;

		pipeline->process(context);
		
		ASSERT_TRUE(actionInvoked);
		ASSERT_TRUE(context.getProperty<bool>("action2"));
		ASSERT_TRUE(context.getProperty<bool>("started"));
	}

	TEST(PipelineBuilderTests, Demo) {
		auto serviceContainer = std::make_shared<ServiceContainer>();
		serviceContainer->singleton<ILoggerFactory, LoggerFactory>();


		PipelineBuilder builder(serviceContainer);

		function<void(PipelineContext&)> action = [](PipelineContext & context) {
			context.setProperty<bool>("action1", true);
		};

		builder
			.use(action, "Action 1")
			.use([](PipelineContext& context)
				{
					context.setProperty<bool>("action2", true);
				}, "Action 2")
			.use([](PipelineContext& context)
				{
					context.setProperty<bool>("action3", true);
				}, "Log properties action")
			.use([](PipelineContext& context)
				{
					context.setProperty<bool>("abort", true);
					context.abort();
				}, "Abort action")
			.use([](PipelineContext& context)
				{
					context.setProperty<bool>("not-executed", false);
				}, "Action not executed")
			;

		auto pipeline = builder.build();


		PipelineContext context;
		context.setProperty<bool>("not-executed", true);


		pipeline->process(context);


		ASSERT_TRUE(context.getProperty<bool>("action1"));
		ASSERT_TRUE(context.getProperty<bool>("action2"));
		ASSERT_TRUE(context.getProperty<bool>("action3"));
		ASSERT_TRUE(context.getProperty<bool>("abort"));
		ASSERT_TRUE(context.getProperty<bool>("not-executed"));

	}
}
