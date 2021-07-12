#pragma once
#include "FileInfo.h"
#include "DirectoryInfo.h"

#include <filesystem>
#include <string>
#include <memory>
#include <vector>


namespace Matrix
{
	class Directory
	{
	public:
		Directory() = delete;

		~Directory() = delete;

		static DirectoryInfo currentPath();

		static bool exists(const std::string& fullPath);

		static bool createDirectory(const std::string& path);

		static DirectoryInfo createIfNotExists(const std::string& path);

		static void remove(const std::string& path, const bool recursive = false);

		static std::vector<FileInfo> getFiles(const std::string& path, const std::string& filter = "", const bool includeSubdirectories = false);

		template<typename T>
		static T join(const T first, const T second)
		{
			return combine(first, second);
		}

		template<typename T, typename ...Args>
		static T join(const T first, const T second, Args ... args)
		{
			return join(join(first, second), args...);
		}

		static std::string combine(const std::string& path1, const std::string& path2);
	};
}

