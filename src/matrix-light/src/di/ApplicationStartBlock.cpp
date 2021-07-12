#include "di/ApplicationStartBlock.h"

namespace Matrix
{
	using std::function;
	using std::shared_ptr;
	using std::string;

	ApplicationStartBlock::ApplicationStartBlock(AppStartAction& action)
		:mAction(action)
	{

	}

	ApplicationStartBlock::ApplicationStartBlock(AppStartAction& action, shared_ptr<ILoggerFactory> loggerFactory, string blockName, int blockOrrder)
		: mAction(action)
	{
		name = blockName;
		order = blockOrrder;

		initLogger(loggerFactory);
	}

	ApplicationStartBlock::~ApplicationStartBlock()
	{
	}

	void ApplicationStartBlock::process(ApplicationStartBlockContext & context)
	{
		if (mAction)
		{
			try
			{
				mLogger->debug("Start invoking block:", name);

				mAction(context);

				mLogger->debug("Finish invoke block:", name).debug("");
			}
			catch (const std::exception & e)
			{
				context.abort();

				mLogger->debug("Invoking block '", name, "' with exception: ", e.what());
			}
		}
	}

	void ApplicationStartBlock::process(PipelineContext & context)
	{
		if (mAction)
		{
			try
			{
				mLogger->debug("Invoking block: ", name);

				ApplicationStartBlockContext appContext(context);

				mAction(appContext);
			}
			catch (const std::exception & e)
			{
				context.abort();

				mLogger->debug("Invoking block '", name, "' with exception: ", e.what());
			}
		}
	}

	shared_ptr<IApplicationStartBlock> ApplicationStartBlock::withName(std::string blockName)
	{
		name = blockName;
		initLogger(nullptr);
		return shared_from_this();
	}

	shared_ptr<IApplicationStartBlock> ApplicationStartBlock::withOrder(int blockOrder)
	{
		order = blockOrder;
		return shared_from_this();
	}

	shared_ptr<IApplicationStartBlock> ApplicationStartBlock::withServices(shared_ptr<IServiceProvider> services)
	{
		mServiceProvider = services;

		initLogger(nullptr);

		return shared_from_this();
	}

	void ApplicationStartBlock::initLogger(shared_ptr<ILoggerFactory> loggerFactory)
	{
		if (mLogger == nullptr)
		{
			std::string loggerName = "ApplicationStartBlock " + name;
			if (loggerFactory)
			{
				mLogger = loggerFactory->createLogger(loggerName);
			}
			else if (mServiceProvider)
			{
				auto factory = mServiceProvider->resolveService<ILoggerFactory>();
				mLogger = factory->createLogger(loggerName);
			}
		}
	}
}
