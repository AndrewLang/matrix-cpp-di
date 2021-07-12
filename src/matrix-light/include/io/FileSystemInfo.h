#pragma once
#include <filesystem>
#include <vector>
#include <memory>
#include <string>
#include <chrono>


namespace Matrix
{
	class FileSystemInfo
	{
	public:
		FileSystemInfo(std::string path);

		~FileSystemInfo() ;

		virtual std::string fullPath();

		virtual std::string name() = 0;

		virtual bool exists();
				
		virtual std::filesystem::file_time_type lastWriteTime();

		virtual bool remove() = 0;
		
	protected: 
		std::string mFullPath;
	};
}