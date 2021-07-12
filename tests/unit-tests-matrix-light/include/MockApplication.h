#pragma once
#include "di/ApplicationBase.h"

namespace Matrix
{
	class MockApplication: public ApplicationBase
	{
	public:
		MockApplication();
		~MockApplication();

	protected :
		void registerServices(std::shared_ptr<IServiceContainer> container) override;
	};

}