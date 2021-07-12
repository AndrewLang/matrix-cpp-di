#include "io/FileInfo.h"
#include "common/StringExtensions.h"

namespace Matrix
{
	namespace fs = std::filesystem;
	using std::string;

	FileInfo::FileInfo(string path)
		: FileSystemInfo(path)
	{
	}

	FileInfo::~FileInfo()
	{
	}

	string FileInfo::name()
	{
		string path = fullPath();
		return 	fs::path(path).filename().string();
	}

	string FileInfo::extension()
	{
		string path = fullPath();
		return 	fs::path(path).extension().string();
	}

	string FileInfo::fileNameWithoutExtension()
	{
		string fileName = name();
		string ext = extension();

		int index = StringExtensions::indexOf(fileName, ext);

		return fileName.substr(0, index);
	}

	string FileInfo::parent()
	{
		string path = fullPath();
		return fs::path(path).parent_path().string();
	}

	long FileInfo::size()
	{
		string path = fullPath();
		return fs::file_size(path);
	}

	bool FileInfo::remove()
	{
		try
		{
			fs::remove(fullPath());

			return true;
		}
		catch (...)
		{
			return false; 			
		}
	}
}