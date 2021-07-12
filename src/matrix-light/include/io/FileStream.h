#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <fstream>


namespace Matrix
{
	enum class FileMode
	{
		CreateNew = 1,
		Create = 2,
		Open = 3,
		OpenOrCreate = 4,
		Truncate = 5,
		Append = 6
	};

	enum class FileAccess
	{
		Read = 1,
		Write = 2,
		ReadWrite = 3
	};

	enum class SeekOrigin
	{
		Begin = 0,
		Current = 1,
		End = 2
	};

	class FileNotOpenException : public std::exception
	{
	public :
		FileNotOpenException(std::string filePath);

		virtual const char* what() const throw ();

	private :
		std::string mFilePath;
	};



	class FileStream
	{
	public:
		FileStream() = delete;

		FileStream(const FileStream& stream) = delete;

		FileStream(std::string filePath, FileMode mode = FileMode::Append, FileAccess access = FileAccess::Read);

		~FileStream();

		std::string getPath();
		
		long length();

		long position();

		bool canRead();

		bool canWrite();

		FileStream& open();

		void close();
			
		FileStream& seek(long offset, SeekOrigin origin = SeekOrigin::Begin);
		
		FileStream& read(char * buffer, const long length);

		FileStream& readLine(std::string& line);

		FileStream& readAll(std::string& content);

		FileStream& write(const std::string content);

		FileStream& writeLine(const std::string content);
		
		FileStream& write(const char * buffer, const long length);

		static std::shared_ptr<FileStream> binary(const std::string filePath);
		
	private:
		std::string mFilePath;
		FileMode mFileMode;
		FileAccess mFileAccess;
		std::fstream mStream;
		long mLength = 0;
		
		std::ios_base::openmode mInitialMode = std::ios_base::app;

	protected:
		std::ios_base::openmode getOpenMode(FileAccess access, FileMode openMode);

		std::ios_base::seekdir getSeekDirction(SeekOrigin origin);

		void guard();

		long getLength();
	};
}