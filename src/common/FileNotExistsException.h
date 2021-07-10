#pragma once
#include "BaseException.h"

namespace Matrix
{

	class FileNotExistsException : public BaseException
	{
	public:
		FileNotExistsException(const std::string& file);

	protected:
		std::string buildMessage() const override;

	private:
		const std::string mFile;
	};

}