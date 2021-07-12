#include "io/FileSystemInfo.h"

namespace Matrix
{
	namespace fs = std::filesystem;
	using std::string;
	using std::filesystem::file_time_type;

	FileSystemInfo::FileSystemInfo(string path) : mFullPath(path)
	{
	}
	
	FileSystemInfo::~FileSystemInfo()
	{
	}

	string FileSystemInfo::fullPath()
	{
		return mFullPath;
	}
	
	bool FileSystemInfo::exists()
	{
		return fs::exists(mFullPath);
	}
	
	file_time_type FileSystemInfo::lastWriteTime()
	{
		return fs::last_write_time(mFullPath);
	}
}