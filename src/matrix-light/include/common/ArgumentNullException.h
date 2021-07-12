#pragma once
#include "BaseException.h"

namespace Matrix
{
	class ArgumentNullException : public BaseException
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