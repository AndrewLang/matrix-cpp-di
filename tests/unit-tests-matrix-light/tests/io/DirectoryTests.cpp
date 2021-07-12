#include "gtest/gtest.h"

#include "io/Directory.h"
#include "TestFiles.h"

namespace Matrix
{
	TEST(DirectoryTests, Exists) {
		TestFiles files;

		ASSERT_TRUE(Directory::exists(files.folder()));
		ASSERT_FALSE(Directory::exists(files.notExistsFolder()));
	}

	TEST(DirectoryTests, CurrentPath) {
		auto dir = Directory::currentPath();

		ASSERT_TRUE(dir.exists());
	}
	TEST(DirectoryTests, CreateRemoveFolder) {
		TestFiles files;

		Directory::createDirectory(files.notExistsFolder());

		ASSERT_TRUE(Directory::exists(files.notExistsFolder()));

		Directory::remove(files.notExistsFolder());

		ASSERT_FALSE(Directory::exists(files.notExistsFolder()));
	}

	TEST(DirectoryTests, GetFiles) {
		TestFiles files;

		auto items = Directory::getFiles(files.folder());

	}

	TEST(DirectoryInfoTests, CreateIfNotExists) {
		TestFiles files;

		auto dirInfo = Directory::createIfNotExists(files.notExistsFolder());
		
		ASSERT_TRUE(dirInfo.exists());

		dirInfo.remove();

		ASSERT_FALSE(dirInfo.exists());
	}

	TEST(DirectoryTests, Combine) {
		#if defined(_WIN32)
		string root = R"(C:\temp)";
		string root1 = R"(C:\temp\)";

		string path1 = R"(subdir\file.txt)";
		string path2 = R"(\subdir\file.txt)";

		string expectFile = R"(C:\temp\subdir\file.txt)";
		#else
		string root = R"(usr/temp)";
		string root1 = R"(usr/temp/)";

		string path1 = R"(subdir/file.txt)";
		string path2 = R"(/subdir/file.txt)";

		string expectFile = R"(usr/temp/subdir/file.txt)";
		#endif

		

		ASSERT_EQ(expectFile, Directory::combine(root, path1));
		ASSERT_EQ(expectFile, Directory::combine(root, path2));

		ASSERT_EQ(expectFile, Directory::combine(root1, path1));
		ASSERT_EQ(expectFile, Directory::combine(root1, path2));
	}

	TEST(DirectoryTests, Join) {
		#if defined(_WIN32)
		string root = R"(C:\temp)";
		string path1 = R"(subdir1\subdir2)";
		string path2 = R"(\subdir3\)";
		string path3 = R"(file.txt)";
		string expect = R"(C:\temp\subdir1\subdir2\subdir3\file.txt)";
		#else 
		string root = R"(usr/temp)";
		string path1 = R"(subdir1/subdir2)";
		string path2 = R"(/subdir3/)";
		string path3 = R"(file.txt)";
		string expect = R"(usr/temp/subdir1/subdir2/subdir3/file.txt)";
		#endif

		string actual = Directory::join(root, path1, path2, path3);

		ASSERT_EQ(expect, actual);
	}
}