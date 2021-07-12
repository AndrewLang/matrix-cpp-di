#pragma once
#include "IApiHandler.h"

namespace Matrix
{
	class ApiHandler : public IApiHandler
	{
	public:
		void handle(std::string name) override;
	};

}