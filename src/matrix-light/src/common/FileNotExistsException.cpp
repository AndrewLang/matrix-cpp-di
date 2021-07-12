#include "common/FileNotExistsException.h"
#include "common/TextFormatter.h"

namespace Matrix
{
	using std::string;


	FileNotExistsException::FileNotExistsException(const string& file)
		: mFile(file)
	{
	}

	string FileNotExistsException::buildMessage() const
	{
		TextFormatter formatter;
		return formatter.format("File: '", mFile, "' is NOT found.");
	}	
}