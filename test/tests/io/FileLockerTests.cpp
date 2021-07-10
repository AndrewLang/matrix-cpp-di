#include "gtest/gtest.h"
#include "windows/WinFileLocker.h"
#include "TestFiles.h"
#include "io/FileInfo.h"

#include <iostream>
#include <fstream>

using std::ofstream;
using std::ifstream;

namespace Matrix
{
	TEST(WinFileLockerTests, LockUnlock) {
		TestFiles files;
		string path = files.getLockFile();

		FileInfo fileInfo(path);

		WinFileLocker locker;
		
		ASSERT_TRUE(locker.lock(path));

		/* Read failed but no error or exception */
		ifstream streamRead(path);
		string line;
		string content;
		while (std::getline(streamRead, line))
		{
			content += line;
		}

		DWORD error = GetLastError();

		ASSERT_FALSE(error == ERROR_SUCCESS);

		ASSERT_EQ("", content);

		ASSERT_TRUE(locker.unlock());
	}
}