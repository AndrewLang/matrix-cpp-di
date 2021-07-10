#pragma once
#include "IApplicationStartBlock.h"
#include "logging/ILoggerFactory.h"
#include "logging/ILogger.h"

#include <functional>
#include <memory>

namespace Matrix
{
	using AppStartAction = std::function<void(ApplicationStartBlockContext&)>;

		
	class ApplicationStartBlock: public IApplicationStartBlock, public std::enable_shared_from_this<ApplicationStartBlock>
	{
	public:
		ApplicationStartBlock(AppStartAction& action);

		ApplicationStartBlock(AppStartAction& action, std::shared_ptr<ILoggerFactory> loggerFactory, std::string blockName, int blockOrrder);
		
		~ApplicationStartBlock();

		virtual void process(ApplicationStartBlockContext & context) override;

		virtual void process(PipelineContext & context) override;

		virtual std::shared_ptr<IApplicationStartBlock> withName(std::string blockName) override;

		virtual std::shared_ptr<IApplicationStartBlock> withOrder(int blockOrder) override;

		virtual std::shared_ptr<IApplicationStartBlock> withServices(std::shared_ptr<IServiceProvider> services) override;
	private:
		AppStartAction mAction;
		std::shared_ptr<ILogger> mLogger;
		std::shared_ptr<IServiceProvider> mServiceProvider;

		void initLogger(std::shared_ptr<ILoggerFactory> loggerFactory);
	};
}