#pragma once
#include <chrono>
#include <string>
#include <sstream>


namespace Matrix
{
	class Stopwatch
	{
	public:	
		Stopwatch& start();

		Stopwatch& stop();

		Stopwatch& reset();

		long long elapsed();

		long long elapsedMilliseconds();

		bool isRunning();

		std::string format();

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> mStart;
		std::chrono::nanoseconds mDuration = std::chrono::nanoseconds::zero();
		bool mIsRunning = false;
	};

}