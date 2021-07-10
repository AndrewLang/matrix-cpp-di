#include "gtest/gtest.h"
#include "io/DirectoryInfo.h"
#include "TestFiles.h"
#include "logging/VsOutput.h"

#include <vector>

namespace Matrix
{
	TEST(DirectoryInfoTests, Constructor) {
		TestFiles files;

		DirectoryInfo dir(files.folder());
	}

	TEST(DirectoryInfoTests, Exists) {
		TestFiles files;

		DirectoryInfo dir(files.folder());

		ASSERT_TRUE(dir.exists());
	}

	TEST(DirectoryInfoTests, NotExists) {
		TestFiles files;

		DirectoryInfo dir(files.notExistsFile());

		ASSERT_FALSE(dir.exists());
	}

	TEST(DirectoryInfoTests, Name) {
		TestFiles files;

		DirectoryInfo dir(files.folder());

		ASSERT_EQ(dir.name(), "files");
	}

	TEST(DirectoryInfoTests, Parent) {
		TestFiles files;

		DirectoryInfo dir(files.folder());

		ASSERT_EQ(dir.parent(), files.rootFolder());
	}

	TEST(DirectoryInfoTests, Root) {
		TestFiles files;

		DirectoryInfo dir(files.folder());

		ASSERT_EQ(dir.root(), "");
	}

	TEST(DirectoryInfoTests, Create) {
		TestFiles files;

		DirectoryInfo dir(files.notExistsFolder());

		ASSERT_FALSE(dir.exists());

		dir.create();

		ASSERT_TRUE(dir.exists());

		dir.remove();

		ASSERT_FALSE(dir.exists());
	}
		
	TEST(DirectoryInfoTests, CreateSubdirectory) {
		TestFiles files;

		DirectoryInfo dir(files.folder());

		DirectoryInfo subDir = dir.createSubdirectory("temp");

		ASSERT_TRUE(subDir.exists());
	}

	TEST(DirectoryInfoTests, Remove) {
		TestFiles files;

		DirectoryInfo dir(files.folder());

		DirectoryInfo subDir = dir.createSubdirectory("temp");

		ASSERT_TRUE(subDir.exists());

		subDir.remove();

		ASSERT_FALSE(subDir.exists());
	}

	TEST(DirectoryInfoTests, EnumerateFiles) {
		TestFiles files;

		DirectoryInfo dir(files.folder());

		auto items = dir.enumerateFiles();

		VsOutput::writeWithName("Files", "");
		for (auto &file : items)
		{
			VsOutput::debugLine(file.fullPath());
		}
	}

	TEST(DirectoryInfoTests, EnumerateDirectories) {
		TestFiles files;

		DirectoryInfo dir(files.folder());

		DirectoryInfo subDir = dir.createSubdirectory("temp");

		auto items = dir.enumerateDirectories();

		VsOutput::writeWithName("Folders", "");
		for (auto &file : items)
		{
			VsOutput::debugLine(file.fullPath());
		}
		subDir.remove();
	}

	TEST(DirectoryInfoTests, EnumerateFilesWithFilter) {
		TestFiles files;

		DirectoryInfo dir(files.getPxisaFolder());

		auto iniFiles = dir.enumerateFiles(".ini");

		ASSERT_EQ(1, iniFiles.size());

		auto txtFiles = dir.enumerateFiles(".txt");

		ASSERT_EQ(1, txtFiles.size());

		VsOutput::writeWithName("Files", "");
		for (auto &file : iniFiles)
		{
			VsOutput::debugLine(file.fullPath());
		}
	}
}