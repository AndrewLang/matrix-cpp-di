#include "common/Exception.h"

namespace Matrix
{
	Exception::Exception()
	{
	}

	char const * Exception::what() const noexcept
	{
		return buildMessage().c_str();
	}

	std::string Exception::buildMessage() const
	{
		return "";
	}	

}