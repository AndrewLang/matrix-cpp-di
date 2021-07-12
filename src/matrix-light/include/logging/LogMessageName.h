#pragma once
#include <string>


namespace Matrix
{
	class LogMessageName
	{
	public:
		LogMessageName(std::string name) : mName(name) {}

		std::string getName() {
			return mName;
		}

	private:
		std::string mName;
	};
}