#pragma once
#include "FileSystemInfo.h"

namespace Matrix
{
	class FileInfo: public FileSystemInfo
	{
	public:
		FileInfo() = delete;

		FileInfo(std::string path);

		~FileInfo();

		std::string name() override;

		std::string extension();

		std::string fileNameWithoutExtension();

		std::string parent();

		long size();

		bool remove() override;
	};
}
