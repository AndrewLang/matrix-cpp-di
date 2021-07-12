#pragma once
#include "FileSystemInfo.h"
#include "FileInfo.h"

#include <vector>


namespace Matrix
{
	class DirectoryInfo : public FileSystemInfo
	{
	public:
		DirectoryInfo() = delete;

		DirectoryInfo(std::string path);

		DirectoryInfo(const DirectoryInfo& dirInfo);

		~DirectoryInfo();

		std::string name() override;

		std::string parent();

		std::string root();

		void create();

		DirectoryInfo createSubdirectory(std::string directoryName);

		bool remove() override;

		std::vector<DirectoryInfo> enumerateDirectories(bool includeSubdirectories = false);

		std::vector<FileInfo> enumerateFiles(const std::string& extension = "", bool includeSubdirectories = false);

	private :
		bool filter(std::string fileName, std::string extension);

	};

}