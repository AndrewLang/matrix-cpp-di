#include "io/FileWatcher.h"
#include "io/Directory.h"
#include "common/StringExtensions.h"


namespace Matrix
{	
	using namespace std::this_thread;
	using namespace std::filesystem;
	using std::string;
	using std::thread;
	using std::function;
	using std::vector;
	using std::exception;

	namespace fs = std::filesystem;

	FileWatcher::FileWatcher()
	{
	}

	FileWatcher::FileWatcher(string path)
	{
		mPath = path;
	}

	FileWatcher::FileWatcher(string path, string filter)
	{
		mPath = path;
		mFilter = filter;
	}

	FileWatcher::~FileWatcher()
	{
		//stop();
	}

	string FileWatcher::getPath()
	{
		return mPath;
	}

	FileWatcher & FileWatcher::setPath(string value)
	{
		if (mPath != value)
		{
			mPath = value;
			if (mStarted)
			{
				restart();
			}
		}
		return *this;
	}

	string FileWatcher::getFilter()
	{
		return mFilter;
	}

	FileWatcher & FileWatcher::setFilter(string value)
	{
		if (mFilter != value)
		{
			mFilter = value;

			mWatchFileExtensions.clear();

			for (auto filter : StringExtensions::split(mFilter, ';'))
			{
				mWatchFileExtensions.insert(filter);
			}

			if (mStarted)
			{
				restart();
			}
		}
		return *this;
	}

	bool FileWatcher::getEnableRaisingEvents()
	{
		return mEnableRaisingEvents;
	}

	FileWatcher & FileWatcher::setEnableRaisingEvents(bool value)
	{
		if (mEnableRaisingEvents != value)
		{
			mEnableRaisingEvents = value;
		}
		return *this;
	}

	bool FileWatcher::getIncludesSubdirectories()
	{
		return mIncludeSubdirectories;
	}

	FileWatcher & FileWatcher::setIncludeSubdirectories(bool value)
	{
		mIncludeSubdirectories = value;
		return *this;
	}

	FileWatcher& FileWatcher::start()
	{
		initializeFiles();

		mStarted = true;

		mWatchThread = std::make_shared<thread>(
			[=] { startWatch(mPath); }
		);

		return *this;
	}

	FileWatcher& FileWatcher::stop()
	{
		if (mStarted)
		{
			mFiles.clear();
			mEnableRaisingEvents = false;
			mStarted = false;

			if (mWatchThread->joinable())
				mWatchThread->join();
		}

		return *this;
	}

	FileWatcher & FileWatcher::onFileCreated(function<void(string&)> handler)
	{
		if (handler)
		{
			mFileCreatedHandlers.push_back(handler);
		}
		return *this;
	}

	FileWatcher & FileWatcher::onFileChanged(function<void(string&)> handler)
	{
		if (handler)
		{
			mFileChangedHandlers.push_back(handler);
		}
		return *this;
	}

	FileWatcher & FileWatcher::onFileDeleted(function<void(string&)> handler)
	{
		if (handler)
		{
			mFileDeletedHandlers.push_back(handler);
		}
		return *this;
	}

	void FileWatcher::restart()
	{
		stop();

		start();
	}

	void FileWatcher::initializeFiles()
	{
		mFiles.clear();

		for (auto &file : enumerateFiles(mPath, mIncludeSubdirectories))
		{
			mFiles[file.fullPath()] = file.lastWriteTime();
		}
	}

	bool FileWatcher::containsFile(string filename)
	{
		auto iterator = mFiles.find(filename);
		return iterator != mFiles.end();
	}

	bool FileWatcher::filter(FileInfo fileEntry)
	{
		if (mFilter != "")
		{

			return isExtensionAllowed(fileEntry.extension());
		}
		else
		{
			return true;
		}
	}

	bool FileWatcher::isExtensionAllowed(string extension)
	{
		auto find = mWatchFileExtensions.find(extension);
		return find != mWatchFileExtensions.end();
	}

	vector<FileInfo> FileWatcher::enumerateFiles(string directory, bool includeSubdirectories)
	{
		vector<FileInfo> files;

		for (auto &item : Directory::getFiles(directory, "", includeSubdirectories))
		{
			if (filter(item))
				files.push_back(item);
		}

		return files;
	}

	void FileWatcher::startWatch(string directory)
	{
		while (mEnableRaisingEvents)
		{
			if (!mStarted)
				break;

			sleep_for(mDelay);

			try
			{
				const fs::path folder(directory);
				if (!fs::exists(folder))
					continue;

				auto iterator = mFiles.begin();
				while (iterator != mFiles.end())
				{
					if (!fs::exists(iterator->first))
					{
						// file is removed, trigger event or call action
						handleFileDeleted(iterator->first);
						iterator = mFiles.erase(iterator);
					}
					else
					{
						iterator++;
					}
				}

				for (auto &file : enumerateFiles(directory, mIncludeSubdirectories))
				{
					auto lastWriteTime = file.lastWriteTime();
					string filePath = file.fullPath();

					if (!containsFile(filePath))
					{
						// new file created
						mFiles[filePath] = lastWriteTime;
						handleFileCreated(filePath);
					}
					else if (mFiles[filePath] != lastWriteTime)
					{
						// file modified
						mFiles[filePath] = lastWriteTime;
						handleFileChanged(filePath);
					}
				}
			}
			catch (exception e)
			{
				auto content = e.what();
			}
			catch (...)
			{
				auto content = "";
			}
		}
	}

	void FileWatcher::handleFileCreated(string path)
	{
		try
		{
			for (auto handler : mFileCreatedHandlers)
			{
				handler(path);
			}
		}
		catch (exception e)
		{

		}
	}

	void FileWatcher::handleFileChanged(string path)
	{
		try
		{
			for (auto handler : mFileChangedHandlers)
			{
				handler(path);
			}
		}
		catch (exception e)
		{

		}
	}

	void FileWatcher::handleFileDeleted(string path)
	{
		try
		{
			for (auto handler : mFileDeletedHandlers)
			{
				handler(path);
			}
		}
		catch (exception e)
		{

		}
	}
}