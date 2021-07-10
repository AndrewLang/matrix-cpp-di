#pragma once
#include <functional>
#include <string>
#include <future>
#include <chrono>


namespace Matrix
{
	template<class TFunction>
	class Do
	{
	public:
		Do(TFunction func) : mFunc(func) { }

		Do<TFunction> sleep(int milliseconds);

		Do<TFunction> attempt(int count);

		template<class... TArgs>
		void start(TArgs&&... args)
		{
			int count = 0;

			while (count < mTryCount)
			{
				try
				{
					mFunc(args...);
					break;
				}
				catch (...)
				{
					count++;
					std::chrono::duration<int, std::milli> delay = std::chrono::milliseconds(mMilliseconds);
					std::this_thread::sleep_for(delay);
				}
			}
		}

	private:
		TFunction mFunc;
		int mMilliseconds = 1000;
		int mTryCount = 10;
	};

	template<class TFunction>
	inline Do<TFunction> Do<TFunction>::sleep(int milliseconds)
	{
		mMilliseconds = milliseconds;
		return *this;
	}
	template<class TFunction>
	inline Do<TFunction> Do<TFunction>::attempt(int count)
	{
		mTryCount = count;
		return *this;
	}
}