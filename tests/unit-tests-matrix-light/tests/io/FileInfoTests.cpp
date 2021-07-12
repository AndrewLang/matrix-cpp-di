#include "gtest/gtest.h"
#include "TestFiles.h"
#include "io/FileInfo.h"

#include <iostream>
#include <fstream> 

namespace Matrix
{
	TEST(FileInfoTests, Constructor) {
		TestFiles files;

		string config = files.getConfiguration();

		FileInfo file(config);
	}
	
	TEST(FileInfoTests, Exists) {
		TestFiles files;

		string config = files.getConfiguration();

		FileInfo file(config);

		ASSERT_TRUE(file.exists());
	}

	TEST(FileInfoTests, ExistsFalse) {
		TestFiles files;

		string config = files.notExistsFile();

		FileInfo file(config);

		ASSERT_FALSE(file.exists());
	}
	
	TEST(FileInfoTests, Name) {
		TestFiles files;

		string config = files.getConfiguration();

		FileInfo file(config);

		ASSERT_EQ(file.name(), "configuration.ini");
	}

	TEST(FileInfoTests, Extension) {
		TestFiles files;

		string config = files.getConfiguration();

		FileInfo file(config);

		ASSERT_EQ(file.extension(), ".ini");

	}

	TEST(FileInfoTests, FileNameWithoutExtension) {
		TestFiles files;

		string config = files.getConfiguration();

		FileInfo file(config);

		ASSERT_EQ(file.fileNameWithoutExtension(), "configuration");
	}

	TEST(FileInfoTests, FullPath) {
		TestFiles files;

		string config = files.getConfiguration();

		FileInfo file(config);

		ASSERT_EQ(file.fullPath(), config);
	}

	TEST(FileInfoTests, LastWriteTime) {
		TestFiles files;

		string config = files.getConfiguration();

		FileInfo file(config);

		file.lastWriteTime();
	}

	TEST(FileInfoTests, Parent) {
		TestFiles files;

		string config = files.getConfiguration();

		FileInfo file(config);

		ASSERT_EQ(file.parent(), files.folder());
	}

	TEST(FileInfoTests, Remove) {
		TestFiles files;
		string temp = files.getFilePath("temp.txt");
		std::ofstream stream(temp);

		stream << "temp file";
		stream.close();

		FileInfo info(temp);

		ASSERT_TRUE(info.exists());

		ASSERT_TRUE(info.remove());

		ASSERT_FALSE(info.exists());
	}

	TEST(FileInfoTests, FileSize) {
		TestFiles files;

		string config = files.getConfiguration();

		FileInfo file(config);

		ASSERT_TRUE(file.size() > 0);
	}
}