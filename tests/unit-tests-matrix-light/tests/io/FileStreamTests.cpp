#include "gtest/gtest.h"
#include "io/FileStream.h"
#include "TestFiles.h"
#include "logging/VsOutput.h"
#include "io/FileInfo.h"

namespace Matrix
{
	TEST(FileStreamTests, ConstructorDefault) {
		TestFiles files;

		FileStream stream(files.getSimulate());

		ASSERT_FALSE(stream.canWrite());
		ASSERT_TRUE(stream.canRead());
		ASSERT_EQ(-1, stream.position());
		ASSERT_EQ(files.getSimulate(), stream.getPath());

		stream.close();
	}

	TEST(FileStreamTests, ConstructorEmptyPath) {

		EXPECT_ANY_THROW(
			FileStream stream("");
		);
	}
	TEST(FileStreamTests, ConstructorWrite) {
		TestFiles files;

		FileStream stream(files.getConfiguration(), FileMode::Open, FileAccess::Write);

		ASSERT_TRUE(stream.canWrite());
		ASSERT_FALSE(stream.canRead());
		ASSERT_EQ(-1, stream.position());
		ASSERT_EQ(files.getConfiguration(), stream.getPath());

		stream.close();
	}

	TEST(FileStreamTests, ConstructorReadWrite) {
		TestFiles files;

		FileStream stream(files.getConfiguration(), FileMode::Open, FileAccess::ReadWrite);

		ASSERT_TRUE(stream.canWrite());
		ASSERT_TRUE(stream.canRead());
		ASSERT_EQ(-1, stream.position());
		ASSERT_EQ(files.getConfiguration(), stream.getPath());

		stream.close();
	}

	TEST(FileStreamTests, FileLength) {
		TestFiles files;

		FileStream stream(files.getConfiguration());
		stream.open();

		ASSERT_TRUE(stream.length() > 0);

		stream.close();
	}

	TEST(FileStreamTests, Seek) {
		TestFiles files;

		FileStream stream(files.getConfiguration());
		stream.open();

		ASSERT_EQ(0, stream.position());


		stream.seek(0, SeekOrigin::End);
		ASSERT_TRUE(stream.position() > 0);

		stream.seek(0, SeekOrigin::Begin);
		ASSERT_EQ(0, stream.position());


		stream.seek(100, SeekOrigin::Begin);
		ASSERT_EQ(100, stream.position());

		stream.close();
	}

	TEST(FileStreamTests, ReadAll) {

		TestFiles files;
		string content;

		FileStream stream(files.getConfiguration());
		stream.open().readAll(content).close();

		VsOutput::writeWithName("File content", content);

		ASSERT_TRUE(content.length() > 0);
	}

	TEST(FileStreamTests, ReadLine) {

		TestFiles files;
		string content;

		FileStream stream(files.getConfiguration());
		stream.open().readLine(content).close();

		VsOutput::writeWithName("First line", content);

		ASSERT_EQ(content, "[Something]");
	}

	TEST(FileStreamTests, Read) {
		TestFiles files;

		auto stream = FileStream::binary(files.getConfiguration());

		stream->open();

		string expected = "[Something]";
		long length = static_cast<long>(expected.length());

		char* buffer = new char[length];

		stream->read(buffer, length).close();

		string actual = string(buffer, 0, length);

		VsOutput::writeWithName("File content", actual);

		ASSERT_EQ(actual, expected);

		delete[] buffer;
	}

	TEST(FileStreamTests, WriteString) {
		TestFiles files;
		string path = files.notExistsFile();
		FileInfo fileInfo(path);
		FileStream streamWrite(path, FileMode::OpenOrCreate, FileAccess::Write);
		streamWrite.open();

		string expected = "[Something]";
		streamWrite.write(expected).close();

		string actual = "";
		FileStream streamRead(path);
		streamRead.open().readAll(actual).close();


		ASSERT_EQ(actual, expected);

		ASSERT_TRUE(fileInfo.remove());

		ASSERT_FALSE(fileInfo.exists());
	}

	TEST(FileStreamTests, WriteLine) {
		TestFiles files;
		string path = files.notExistsFile();
		FileInfo fileInfo(path);
		FileStream streamWrite(path, FileMode::OpenOrCreate, FileAccess::Write);
		streamWrite.open();

		string expected = "[Something]";
		streamWrite.writeLine(expected).close();

		string actual = "";
		FileStream streamRead(path);
		streamRead.open().readAll(actual).close();


		ASSERT_EQ(actual, expected);

		ASSERT_TRUE(fileInfo.remove());

		ASSERT_FALSE(fileInfo.exists());
	}

	TEST(FileStreamTests, WriteChars) {
		TestFiles files;
		string path = files.notExistsFile();
		FileInfo fileInfo(path);
		FileStream streamWrite(path, FileMode::OpenOrCreate, FileAccess::Write);
		streamWrite.open();

		string expected = "[Something]";
		long length = static_cast<long>(expected.length());

		char* value = const_cast<char*>(expected.c_str());
		streamWrite.write(value, length).close();

		string actual = "";
		FileStream streamRead(path);
		streamRead.open().readAll(actual).close();


		ASSERT_EQ(actual, expected);

		ASSERT_TRUE(fileInfo.remove());
		ASSERT_FALSE(fileInfo.exists());
	}
}