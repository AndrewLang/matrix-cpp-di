#include "common/FileLoadException.h"
#include "common/TextFormatter.h"

namespace Matrix
{
	using std::string;

	FileLoadException::FileLoadException(const string fileName)
		: mFileName(fileName)
	{
	}

	string FileLoadException::buildMessage() const
	{
		TextFormatter formatter;
		return formatter.format("Load file '", mFileName, "' failed.");
	}
}