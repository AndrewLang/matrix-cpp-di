#include "io/FileStream.h"
#include "common/Guard.h"
#include "common/ArgumentNullException.h"
#include "common/StringExtensions.h"
#include "common/TextFormatter.h"


namespace Matrix
{
	using std::ifstream;
	using std::shared_ptr;
	using std::ios_base;
	using std::string;


	FileNotOpenException::FileNotOpenException(string filePath)
		: mFilePath(filePath)
	{

	}

	const char * FileNotOpenException::what() const throw()
	{
		TextFormatter formatter;
		return formatter.format("FileStream: '", mFilePath, "' was not opened.").c_str();
	}



	FileStream::FileStream(string filePath, FileMode mode, FileAccess access)
		:mFilePath(filePath), mFileMode(mode), mFileAccess(access)
	{
		if (StringExtensions::isNullOrEmpty(filePath))
			throw ArgumentNullException("filePath");
	}

	FileStream::~FileStream()
	{

	}

	string FileStream::getPath()
	{
		return mFilePath;
	}

	long FileStream::length()
	{
		return mLength;
	}

	long FileStream::position()
	{
		if (!mStream)
			return 0;

		return static_cast<long>(mStream.tellg());
	}

	bool FileStream::canRead()
	{
		return mFileAccess != FileAccess::Write;
	}

	bool FileStream::canWrite()
	{
		return mFileAccess != FileAccess::Read;
	}

	FileStream & FileStream::open()
	{
		auto mode = getOpenMode(mFileAccess, mFileMode);		
		mStream.open(mFilePath, mode);

		mLength = getLength();

		return *this;
	}

	void FileStream::close()
	{		
		if(mStream.is_open())
			mStream.close();
	}
		
	FileStream & FileStream::seek(long offset, SeekOrigin origin)
	{
		guard();

		if (mStream.is_open())
		{
			mStream.seekg(offset, getSeekDirction(origin));
		}

		return *this;
	}

	FileStream & FileStream::read(char * buffer, const long length)
	{
		guard();
				
		if (mStream.is_open())
		{			 
			mStream.read(buffer, length);
		}

		return *this;
	}

	FileStream & FileStream::readLine(string & line)
	{
		guard();

		if (mStream.is_open())
		{
			std::getline(mStream, line);
		}

		return *this;
	}

	FileStream & FileStream::readAll(string & content)
	{
		guard();

		if (mStream.is_open())
		{
			string line;
			std::stringstream stream;

			while (std::getline(mStream, line))
			{
				stream << line; // << std::endl;
			}

			content = stream.str();			
		}

		return *this;
	}
	
	FileStream & FileStream::write(const string content)
	{
		guard();

		if (mStream.is_open())
		{
			mStream << content;
		}

		return *this;
	}

	FileStream & FileStream::writeLine(const string content)
	{
		guard();

		if (mStream.is_open())
		{
			mStream << content << std::endl;
		}

		return *this;
	}

	FileStream & FileStream::write(const char * buffer, const long length)
	{
		guard();

		if (mStream.is_open())
		{
			mStream.write(buffer, length);
		}

		return *this;
	}

	shared_ptr<FileStream> FileStream::binary(const string filePath)
	{
		auto stream = std::make_shared<FileStream>(filePath);
		stream->mInitialMode = ios_base::binary;
		return stream;
	}
	
	ios_base::openmode FileStream::getOpenMode(FileAccess access, FileMode openMode)
	{
		ios_base::openmode mode = mInitialMode;

		switch (access)
		{
		case Matrix::FileAccess::Read:
			mode = mode | ios_base::in;
			break;
		case Matrix::FileAccess::Write:
			mode = mode | ios_base::out;
			break;
		case Matrix::FileAccess::ReadWrite:
		default:
			mode = mode | ios_base::in | ios_base::out;
			break;
		}

		switch (openMode)
		{
		case Matrix::FileMode::CreateNew:
			break;
		case Matrix::FileMode::Create:
			break;
		case Matrix::FileMode::Open:
			break;
		case Matrix::FileMode::OpenOrCreate:
			break;
		case Matrix::FileMode::Truncate:
			mode = mode | ios_base::trunc;
			break;
		case Matrix::FileMode::Append:
			mode = mode | ios_base::app;
			break;
		default:
			break;
		}

		return mode;
	}

	ios_base::seekdir FileStream::getSeekDirction(SeekOrigin origin)
	{
		auto result = ios_base::beg;
		switch (origin)
		{
		case Matrix::SeekOrigin::Begin:
			result = ios_base::beg;
			break;
		case Matrix::SeekOrigin::Current:
			result = ios_base::cur;
			break;
		case Matrix::SeekOrigin::End:
			result = ios_base::end;
			break;
		}
		return result;
	}

	void FileStream::guard()
	{
		if (!mStream)
			throw FileNotOpenException(mFilePath);
	}

	long FileStream::getLength()
	{
		ifstream stream;
		stream.open(mFilePath, ifstream::binary);
		stream.seekg(0, ios_base::end);
		long size = static_cast<long>(stream.tellg());
		stream.close();

		return size;
	}
	
}