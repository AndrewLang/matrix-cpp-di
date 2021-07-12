#include "task/Task.h"

namespace Matrix
{
	using std::string;
	using std::shared_ptr;


	Task::Task(Action action)
		: mAction(action)
	{
	}

	Task::Task(const Task & task)
	{
		mAction = task.mAction;
	}

	Task::~Task()
	{
	}

	shared_ptr<Task> Task::delay(const long milliseconds, const string & name)
	{
		Action action = [=]() {
			std::chrono::duration<int, std::milli> delay = std::chrono::milliseconds(milliseconds);
			std::this_thread::sleep_for(delay);
		};
		auto task = std::make_shared<Task>(action);
		task->withName(name).start();

		return task;
	}

	void Task::waitAll(std::initializer_list<Task> tasks)
	{
		for (auto task : tasks)
		{
			task.start().wait();
		}
	}

	shared_ptr<Task> Task::tryDo(Action action, const int & count, const int & delayInMilliseconds)
	{		
		Action taskAction = [=]()
		{			
			int tryCount = 0;

			while (tryCount < count)
			{
				try
				{
					tryCount++;

					action();

					break;
				}
				catch (...)
				{
					std::chrono::duration<int, std::milli> delay = std::chrono::milliseconds(delayInMilliseconds);
					std::this_thread::sleep_for(delay); 
					continue;
				}
			}
		};		

		auto task = std::make_shared<Task>(taskAction);
		task->withName("TryDoTask").start();

		return task;
	}

	shared_ptr<Task> Task::execute(Action action)
	{
		Action taskAction = [=]()
		{	
			try
			{
				action();
			}
			catch (...)
			{

			}
		};

		auto task = std::make_shared<Task>(taskAction);
		task->withName("TryExecuteTask").start();

		return task;
	}
	   
	Task & Task::start()
	{
		mFuture = async(mAction);

		return *this;
	}

	Task & Task::wait()
	{
		mFuture.get();

		return *this;
	}

	Task & Task::withName(const string &  taskName)
	{
		name = taskName;
		return *this;
	}
}