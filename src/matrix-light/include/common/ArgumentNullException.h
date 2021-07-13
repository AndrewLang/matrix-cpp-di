#pragma once
#include "Exception.h"

namespace Matrix
{
	class ArgumentNullException : public Exception
	{
	public:
		ArgumentNullException(const std::string argument);
		
		std::string getArgument() const;
	private :
		const std::string mArgument;

	protected:
		std::string buildMessage() const override ;
	};
}