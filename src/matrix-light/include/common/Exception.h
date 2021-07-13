#pragma once

#include <exception>
#include <string>

namespace Matrix
{
	class Exception : public std::exception
	{
	public:
		Exception();
		
		virtual char const * what() const noexcept;

	protected:
		virtual std::string buildMessage() const;
	};

}