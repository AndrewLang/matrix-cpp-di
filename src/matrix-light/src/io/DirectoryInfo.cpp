#include "io/DirectoryInfo.h"
#include "common/StringExtensions.h"

namespace Matrix
{
	namespace fs = std::filesystem;
	using std::string;
	using std::vector;


	DirectoryInfo::DirectoryInfo(string path)
		: FileSystemInfo(path)
	{
	}

	DirectoryInfo::DirectoryInfo(const DirectoryInfo & dirInfo)
		: FileSystemInfo(dirInfo.mFullPath)
	{
	}

	DirectoryInfo::~DirectoryInfo()
	{
	}

	string DirectoryInfo::name()
	{
		string path = fullPath();
		return 	fs::path(path).filename().string();
	}

	string DirectoryInfo::parent()
	{
		string path = fullPath();
		return fs::path(path).parent_path().string();
	}

	string DirectoryInfo::root()
	{
		string path = fullPath();
		return fs::path(path).root_directory().string();
	}

	void DirectoryInfo::create()
	{
		try
		{
			fs::create_directory(fullPath());
		}
		catch (...)
		{

		}
	}

	DirectoryInfo DirectoryInfo::createSubdirectory(string directoryName)
	{
		if (!exists())
			create();

		DirectoryInfo info("");

		try
		{
			fs::path path(fullPath());
			path.append(directoryName);

			fs::create_directory(path.string());

			DirectoryInfo dirInfo(path.string());
			info = dirInfo;

			return info;
		}
		catch (...)
		{

		}

		return info;
	}

	bool DirectoryInfo::remove()
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

	vector<DirectoryInfo> DirectoryInfo::enumerateDirectories(bool includeSubdirectories)
	{
		vector<DirectoryInfo> directories;

		const fs::path path(fullPath());
		if (fs::exists(path) && fs::is_directory(path))
		{
			if (includeSubdirectories)
			{
				for (auto &item : fs::recursive_directory_iterator(path))
				{
					if (item.is_directory())
					{
						DirectoryInfo directoryInfo(item.path().string());
						directories.push_back(directoryInfo);
					}
				}
			}
			else
			{
				for (auto &item : fs::directory_iterator(path))
				{
					if (item.is_directory())
					{
						DirectoryInfo directoryInfo(item.path().string());
						directories.push_back(directoryInfo);
					}
				}
			}
		}

		return directories;
	}

	vector<FileInfo> DirectoryInfo::enumerateFiles(const string& extension, bool includeSubdirectories)
	{
		vector<FileInfo> files;

		const fs::path path(fullPath());
		if (fs::exists(path) && fs::is_directory(path))
		{
			if (includeSubdirectories)
			{
				for (auto &item : fs::recursive_directory_iterator(path))
				{
					if (item.is_regular_file() && filter(item.path().string(), extension))
					{
						FileInfo fileInfo(item.path().string());
						files.push_back(fileInfo);
					}
				}
			}
			else
			{
				for (auto &item : fs::directory_iterator(path))
				{
					if (item.is_regular_file() && filter(item.path().string(), extension))
					{
						FileInfo fileInfo(item.path().string());
						files.push_back(fileInfo);

					}
				}
			}
		}

		return files;
	}

	bool DirectoryInfo::filter(std::string fileName, std::string extension)
	{
		if (Strings::isNullOrEmpty(extension))
			return true;

		return Strings::compareIgnoreCase(fs::path(fileName).extension().string(), extension);
	}
}