#pragma once

#include "common/ObjectMap.h"
#include "services/DataContext.h"
#include <map>
#include <string>
#include <any>


namespace Matrix
{
	class PipelineContext : public DataContext
	{
	public:		
		PipelineContext();

		PipelineContext(std::shared_ptr<IServiceProvider> serviceProvider);

		void abort();

		bool isAborted() const;
				
	private:		
		bool mRequestAborted = false;
	};
}