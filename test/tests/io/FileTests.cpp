#include "gtest/gtest.h"
#include "io/File.h"
#include "TestFiles.h"
#include "io/FileStream.h"
#include "common/StringExtensions.h"

#include <iostream>
#include <fstream> 

namespace Matrix
{
	TEST(FileTests, Exists) {

		TestFiles files;

		ASSERT_TRUE(File::exists(files.getConfiguration()));
		ASSERT_FALSE(File::exists(files.notExistsFile()));
	}

	TEST(FileTests, Remove) {

		TestFiles files;
		string temp = files.getFilePath("temp.txt");


		std::ofstream stream(temp);

		stream << "temp file";
		stream.close();

		ASSERT_TRUE(File::remove(temp));
	}

	TEST(FileTests, LastWriteTime) {

		TestFiles files;

		string config = files.getConfiguration();

		File::lastWriteTime(config);
	}

	TEST(FileTests, ReadAllText) {

		TestFiles files;

		string content = File::readAllText(files.getConfiguration());

		ASSERT_TRUE(content.length() > 0);
	}

	TEST(FileTests, WriteAllText) {

		TestFiles files;
		string path = files.notExistsFile();
		string expected = "[ResourceManager]";

		File::writeAllText(path, expected);

		string actual = "";
		FileStream streamRead(path);
		streamRead.open().readAll(actual).close();

		ASSERT_EQ(actual, expected);

		ASSERT_TRUE(File::remove(path));
		ASSERT_FALSE(File::exists(path));
	}

	TEST(FileTests, GetParent) {
		TestFiles files;

		string file = files.notExistsFile();
		string parent = File::getParent(file);

		ASSERT_TRUE(Strings::compareIgnoreCase(parent, files.folder()));
	}

}