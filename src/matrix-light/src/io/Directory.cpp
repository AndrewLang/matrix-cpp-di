#include "io/Directory.h"
#include "common/StringExtensions.h"

namespace Matrix
{
	using std::string;
	using std::vector;

#if defined(_WIN32)
	const static char PathSeparator = '\\';
#elif defined(__linux__)
	const static char PathSeparator = '/';
#endif

	namespace fs = std::filesystem;

	DirectoryInfo Directory::currentPath()
	{
		DirectoryInfo dirInfo(fs::current_path().string());
		return dirInfo;
	}

	bool Directory::exists(const string & fullPath)
	{
		return fs::exists(fullPath);
	}

	bool Directory::createDirectory(const string & path)
	{
		try
		{
			fs::create_directory(path);

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	DirectoryInfo Directory::createIfNotExists(const string & path)
	{
		if (!exists(path))
			Directory::createDirectory(path);

		DirectoryInfo dirInfo(path);

		return dirInfo;
	}

	void Directory::remove(const string & path, const bool recursive)
	{
		try
		{
			if (recursive)
				fs::remove_all(path);
			else
				fs::remove(path);
		}
		catch (...)
		{

		}
	}

	vector<FileInfo> Directory::getFiles(const string & path, const string& filter, const bool includeSubdirectories)
	{
		DirectoryInfo dirInfo(path);

		return dirInfo.enumerateFiles(filter, includeSubdirectories);
	}

	string Directory::combine(const string & path1, const string & path2)
	{
		string fullPath = path1;

		if (!StringExtensions::endsWith(path1, PathSeparator))
		{
			fullPath = path1 + PathSeparator;
		}

		if (!StringExtensions::startsWith(path2, PathSeparator))
		{
			fullPath += path2;
		}
		else
		{
			fullPath += path2.substr(1, path2.size() - 1);
		}

		return fullPath;
	}

}