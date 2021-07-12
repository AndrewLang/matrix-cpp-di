#pragma once
#include <functional>
#include <string>
#include <future>


namespace Matrix
{
	template<class TKey, class... TArgs>
	using Func = std::function<TKey(TArgs&&... args)>;


	template<class TKey, class TFunction>
	class TaskWithResult
	{
	public:		
		TaskWithResult(TFunction func);

		~TaskWithResult();

		TKey wait();
		
		template<class...TArgs>
		TaskWithResult<TKey,TFunction>& start(TArgs&&... args)
		{
			mFuture = async(std::launch::async, mFunction, args...);
			return *this;
		}

		TaskWithResult<TKey, TFunction>& withName(const std::string & taskName);

		std::string name;

	private:
		TFunction mFunction;
		std::future<TKey> mFuture;
	};

	template<class TKey, class TFunction>
	inline TaskWithResult<TKey, TFunction>::TaskWithResult(TFunction func)		
	{
		mFunction = func;
	}

	template<class TKey, class TFunction>
	inline TaskWithResult<TKey, TFunction>::~TaskWithResult()
	{
	}

	template<class TKey, class TFunction>
	inline TKey TaskWithResult<TKey, TFunction>::wait()
	{
		return mFuture.get();
	}

	template<class TKey, class TFunction>
	inline TaskWithResult<TKey, TFunction>& TaskWithResult<TKey, TFunction>::withName(const std::string & taskName)
	{
		name = taskName;
		return *this;
	}
}