#pragma once
#include <string>

namespace Matrix
{
	class IApiHandler
	{
	public:
		virtual void handle(std::string name) = 0;
	};

}
