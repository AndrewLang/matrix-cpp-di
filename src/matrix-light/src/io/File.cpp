#include "io/File.h"
#include "io/FileInfo.h"
#include "io/FileStream.h"

namespace Matrix
{	
	using std::string;
	using std::filesystem::file_time_type;
	namespace fs = std::filesystem;


	bool File::exists(const string & fullPath)
	{
		FileInfo fileInfo(fullPath);
		return fileInfo.exists();
	}

	bool File::remove(const string & fullPath)
	{
		FileInfo fileInfo(fullPath);
		return fileInfo.remove();
	}

	file_time_type File::lastWriteTime(const string& fullPath)
	{
		FileInfo fileInfo(fullPath);
		return fileInfo.lastWriteTime();
	}

	string File::readAllText(const string & fullPath)
	{
		FileStream stream(fullPath);
		string content;
		stream.open().readAll(content).close();

		return content;
	}

	void File::writeAllText(const string & fullPath, const string & contents)
	{
		FileStream stream(fullPath);
		
		stream.open().write(contents).close();
	}

	string File::getParent(const string& fileName)
	{
		return fs::path(fileName).parent_path().string();
	}
}