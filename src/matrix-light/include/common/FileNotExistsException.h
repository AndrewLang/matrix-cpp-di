#pragma once
#include "Exception.h"

namespace Matrix
{

	class FileNotExistsException : public Exception
	{
	public:
		FileNotExistsException(const std::string file);

	protected:
		std::string buildMessage() const override;

	private:
		const std::string mFile;
	};

}