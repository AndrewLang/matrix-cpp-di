#pragma once
#include <functional>
#include <string>
#include <future>
#include <memory>




namespace Matrix
{
	using Action = std::function<void()>;

	template<class... TArgs>
	using ActionArgs = std::function<void(TArgs&&... args)>;
		
		
	class Task
	{
	public:
		Task(Action action);

		Task(const Task& task);

		~Task();

		static std::shared_ptr<Task> delay(const long milliseconds, const std::string & name = "delay");

		static void waitAll(std::initializer_list<Task> tasks);

		static std::shared_ptr<Task> tryDo(Action action, const int& count = 10, const int& delayInMilliseconds = 1000);

		static std::shared_ptr<Task> execute(Action action);
		
		Task& start();

		Task& wait();

		Task& withName(const std::string &  taskName);

		std::string name;

	private:
		Action mAction;
		std::future<void> mFuture;
	};
	
}