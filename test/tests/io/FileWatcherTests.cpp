#include "gtest/gtest.h"
#include "io/FileWatcher.h"
#include "logging/ConsoleLogger.h"
#include "logging/ILogger.h"
#include "TestFiles.h"

#if defined(_WIN32)
#include "logging/VsOutputLogger.h"
#endif

#include <fstream>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;
using std::thread;

namespace Matrix
{
	void TestFileChange(string filter = "")
	{
#if defined(_WIN32)
		shared_ptr<ILogger> logger = std::make_shared<VsOutputLogger>("FileWatcherTests");
#else
		shared_ptr<ILogger> logger = std::make_shared<ConsoleLogger>("FileWatcherTests");
#endif
		

		TestFiles files;
		string currentPath = files.getCurrentPath();
		string tempFolder = files.getTempFolder();

		logger->debug("Current path: ", currentPath)
			  .debug("Temp folder: ", tempFolder)
			  ;

		fs::path path(currentPath);
		fs::path folder = path.append(tempFolder);

		if (!fs::exists(folder))
		{
			fs::create_directory(folder);
		}

		logger->debug("Destination folder: ", folder.string())
				.debug("");

		FileWatcher watcher(folder.string());
		watcher.setFilter(filter);

		string filename = "watcher.txt";
		string fullPath = folder.append(filename).string();
		std::chrono::duration<int, std::milli> delay = std::chrono::milliseconds(1000);


		bool fileCreated = false;
		bool fileChanged = false;
		bool fileDeleted = false;
		string createdFile = "";
		string changedFile = "";
		string deletedFile = "";

		watcher.onFileCreated([&](string file) {
			fileCreated = true;
			createdFile = file;
		});
		watcher.onFileChanged([&](string file) {
			fileChanged = true;
			changedFile = file;
		});
		watcher.onFileDeleted([&](string file) {
			fileDeleted = true;
			deletedFile = file;
		});

		watcher.start();

		std::ofstream stream(fullPath);
		stream << "file content" << std::endl;
		stream.close();

		std::this_thread::sleep_for(delay);

		std::ofstream stream1(fullPath);
		stream1 << "file content update" << std::endl;
		stream1.close();

		std::this_thread::sleep_for(delay);

		fs::remove(fullPath);

		std::this_thread::sleep_for(delay);


		ASSERT_TRUE(fileCreated);
		ASSERT_TRUE(fileChanged);
		ASSERT_TRUE(fileDeleted);

		ASSERT_EQ(fullPath, createdFile);
		ASSERT_EQ(fullPath, changedFile);
		ASSERT_EQ(fullPath, deletedFile);

		watcher.stop();
	}

	TEST(FileWatcherTests, Constructor) {
		FileWatcher watcher;
	}

	TEST(FileWatcherTests, ConstructorWithPath) {
		FileWatcher watcher("path");

		ASSERT_EQ("path", watcher.getPath());
	}

	TEST(FileWatcherTests, ConstructorWithFilter) {
		FileWatcher watcher("path", "*.txt");

		ASSERT_EQ("path", watcher.getPath());
		ASSERT_EQ("*.txt", watcher.getFilter());
	}

	TEST(FileWatcherTests, Path) {
		FileWatcher watcher;

		ASSERT_EQ("", watcher.getPath());

		watcher.setPath("test");
		ASSERT_EQ("test", watcher.getPath());
	}

	TEST(FileWatcherTests, Filter) {
		FileWatcher watcher;

		ASSERT_EQ("", watcher.getFilter());

		watcher.setFilter("test");
		ASSERT_EQ("test", watcher.getFilter());
	}

	TEST(FileWatcherTests, IncludeSubdirectories) {
		FileWatcher watcher;

		ASSERT_EQ(false, watcher.getIncludesSubdirectories());

		watcher.setIncludeSubdirectories(true);
		ASSERT_EQ(true, watcher.getIncludesSubdirectories());
	}

	TEST(FileWatcherTests, EnableRaisingEvents) {
		FileWatcher watcher;

		ASSERT_EQ(true, watcher.getEnableRaisingEvents());

		watcher.setEnableRaisingEvents(false);
		ASSERT_EQ(false, watcher.getEnableRaisingEvents());
	}

	TEST(FileWatcherTests, WatchFilechanges) {
		TestFileChange();
	}

	TEST(FileWatcherTests, WatchFilechangesWithFilter) {
		TestFileChange(".txt");
	}
		
	TEST(FileWatcherTests, WatchFilechangesWithMultiFilter) {
		TestFileChange(".txt;.ini;.mp3");
	}
}