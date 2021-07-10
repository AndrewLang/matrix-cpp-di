#include "common/Stopwatch.h"


namespace Matrix
{

	Stopwatch::Stopwatch()
	{
	}

	Stopwatch::~Stopwatch()
	{
	}

	Stopwatch & Stopwatch::start()
	{
		if (!mIsRunning) 
		{
			mStart = std::chrono::high_resolution_clock::now();
			mIsRunning = true;
		}
		return *this;
	}

	Stopwatch & Stopwatch::stop()
	{
		if (mIsRunning) 
		{
			auto now = std::chrono::high_resolution_clock::now();

			mDuration = now - mStart;
			mIsRunning = false;
		}
		return *this;
	}

	Stopwatch & Stopwatch::reset()
	{		
		mDuration = std::chrono::nanoseconds::zero();
		mIsRunning = false;
		return *this;
	}

	long long Stopwatch::elapsed()
	{
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(mDuration);
		return seconds.count();
	}

	long long Stopwatch::elapsedMilliseconds()
	{
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(mDuration);
		return milliseconds.count();
	}

	bool Stopwatch::isRunning()
	{
		return mIsRunning;
	}

	std::string Stopwatch::format()
	{
		std::stringstream stream;

		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(mDuration).count();
		long long hour = milliseconds / 3600000;
		milliseconds -= hour * 3600000;

		long long minute = milliseconds / 60000;
		milliseconds -= minute * 60000;

		long long second = milliseconds / 1000;
		milliseconds -= second * 1000;

		stream << hour << ":" << minute << ":" << second << "." << milliseconds;

		return stream.str();
	}
}