#pragma once
#include <functional>
#include <string>
#include <future>
#include <chrono>


namespace Matrix
{
	template<class TKey, class TFunction>
	class DoWithResult
	{
	public:

		DoWithResult(TFunction func): mFunc(func) { }
		
		DoWithResult<TKey, TFunction> sleep(int milliseconds);

		DoWithResult<TKey, TFunction> attempt(int count);

		template<class... TArgs>
		TKey start(TArgs&&... args)
		{
			TKey result;
			int count = 0;

			while (count < mTryCount)
			{
				try
				{
					result = mFunc(args...);
					break;
				}
				catch (...)
				{
					count++;
					std::chrono::duration<int, std::milli> delay = std::chrono::milliseconds(mMilliseconds);
					std::this_thread::sleep_for(delay);
				}
			}

			return result;
		}

	private :
		TFunction mFunc;
		int mMilliseconds = 1000;
		int mTryCount = 10;
	};	

	template<class TKey, class TFunction>
	inline DoWithResult<TKey, TFunction> DoWithResult<TKey, TFunction>::sleep(int milliseconds)
	{
		mMilliseconds = milliseconds;
		return *this;
	}

	template<class TKey, class TFunction>
	inline DoWithResult<TKey, TFunction> DoWithResult<TKey, TFunction>::attempt(int count)
	{
		mTryCount = count;
		return *this;
	}
			
}