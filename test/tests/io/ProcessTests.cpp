#include "gtest/gtest.h"
#include "io/Process.h"

namespace Matrix
{
	using namespace std;

#if defined(_WIN32)
	std::string BlankAppPath = "blank-app.exe";
#elif defined(__linux__)
	std::string BlankAppPath = "./blank-app";
#endif

	TEST(ProcessTests, Start) {
		Process process (BlankAppPath); 

		ASSERT_TRUE(process.isRunning());
		ASSERT_TRUE(process.getId() != 0);
		ASSERT_EQ(BlankAppPath, process.fileName());

		process.terminate();
	}

	TEST(ProcessTests, StartWithArgs) {
		Process process(BlankAppPath, "500");

		ASSERT_TRUE(process.isRunning());
		ASSERT_EQ(BlankAppPath, process.fileName());
		ASSERT_EQ("500", process.arguments());

		process.terminate();
	}

	TEST(ProcessTests, StartWithMultiArgs) {
		Process process(BlankAppPath, "500 20" );

		ASSERT_TRUE(process.isRunning());
		ASSERT_EQ(BlankAppPath, process.fileName());
		ASSERT_EQ("500 20", process.arguments());

		process.terminate();
	}

	TEST(ProcessTests, Wait) {
		Process process(BlankAppPath, "500");

		ASSERT_TRUE(process.isRunning());
		ASSERT_EQ(BlankAppPath, process.fileName());

		bool actual = process.wait(3000);

		ASSERT_TRUE(actual);

		process.terminate();
	}

	TEST(ProcessTests, WaitExit) {
		Process process(BlankAppPath, "500");

		ASSERT_TRUE(process.isRunning());
		ASSERT_EQ(BlankAppPath, process.fileName());

		bool actual = process.wait();

		ASSERT_TRUE(actual);

		process.terminate();
	}
}