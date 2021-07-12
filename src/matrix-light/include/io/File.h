#pragma once
#include <filesystem>
#include <string>


namespace Matrix
{
	class File
	{
	public:
		File() = delete;

		~File() = delete;

		static bool exists(const std::string& fullPath);

		static bool remove(const std::string& fullPath);

		static std::filesystem::file_time_type lastWriteTime(const std::string& fullPath);

		static std::string readAllText(const std::string& fullPath);

		static void writeAllText(const std::string& fullPath, const std::string& contents);

		static std::string getParent(const std::string& fileName);
	};

}