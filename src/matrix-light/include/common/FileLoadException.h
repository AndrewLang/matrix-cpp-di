#pragma once
#include "Exception.h"

namespace Matrix
{
	class FileLoadException : public Exception
	{
	public:
		FileLoadException(const std::string fileName);

	protected:
		std::string buildMessage() const override;

	private: 
		const std::string mFileName;
	};

}