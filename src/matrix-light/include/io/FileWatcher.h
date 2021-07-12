#pragma once
#include "FileInfo.h"

#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <set>


namespace Matrix
{

	class FileWatcher
	{
	public:
		FileWatcher();
		FileWatcher(std::string path);
		FileWatcher(std::string path, std::string filter);
		~FileWatcher();


		std::string getPath();
		FileWatcher& setPath(std::string value);

		std::string getFilter();
		FileWatcher& setFilter(std::string value);

		bool getEnableRaisingEvents();
		FileWatcher& setEnableRaisingEvents(bool value);

		bool getIncludesSubdirectories();
		FileWatcher& setIncludeSubdirectories(bool value);

		FileWatcher& start();
		FileWatcher& stop();

		FileWatcher& onFileCreated(std::function<void(std::string&)> handler);
		FileWatcher& onFileChanged(std::function<void(std::string&)> handler);
		FileWatcher& onFileDeleted(std::function<void(std::string&)> handler);

	private:
		std::string mPath;
		std::string mFilter;
		bool mEnableRaisingEvents = true;
		bool mIncludeSubdirectories = false;
		bool mStarted = false;
		std::shared_ptr<std::thread> mWatchThread;

		std::unordered_map<std::string, std::filesystem::file_time_type> mFiles;
		std::chrono::duration<int, std::milli> mDelay = std::chrono::milliseconds(500);
		std::vector<std::function<void(std::string&)>> mFileCreatedHandlers;
		std::vector<std::function<void(std::string&)>> mFileChangedHandlers;
		std::vector<std::function<void(std::string&)>> mFileDeletedHandlers;
		std::set<std::string> mWatchFileExtensions;

		void restart();
		void initializeFiles();
		bool containsFile(std::string filename);
		bool filter(FileInfo fileEntry);
		bool isExtensionAllowed(std::string extension);

		void startWatch(std::string directory);
		void handleFileCreated(std::string path);
		void handleFileChanged(std::string path);
		void handleFileDeleted(std::string path);

		std::vector<FileInfo> enumerateFiles(const std::string directory, bool includeSubdirectories);
	};

}