#include "gtest/gtest.h"
#include "common/Stopwatch.h"
#include "logging/VsOutput.h"
#include <thread>
#include <chrono>

using std::thread;
using namespace std;

namespace Matrix
{
	TEST(StopwatchTests, Constructor) {
		Stopwatch watch;
	}

	TEST(StopwatchTests, IsRuning) {
		Stopwatch watch;

		ASSERT_FALSE(watch.isRunning());

		watch.start();

		ASSERT_TRUE(watch.isRunning());

		watch.stop();
		ASSERT_FALSE(watch.isRunning());

		watch.reset();
		ASSERT_FALSE(watch.isRunning());
	}

	TEST(StopwatchTests, StartStop) {
		Stopwatch watch;

		std::chrono::duration<int, std::milli> delay = std::chrono::milliseconds(1024);

		watch.start();

		std::this_thread::sleep_for(delay);

		watch.stop();

		VsOutput::writeWithName("Stopwatch", watch.elapsed());
		VsOutput::writeWithName("Stopwatch", watch.elapsedMilliseconds());
		VsOutput::writeWithName("Stopwatch", watch.format());

		watch.reset();

		ASSERT_EQ(0, watch.elapsed());
		ASSERT_EQ(0, watch.elapsedMilliseconds());
	}
}