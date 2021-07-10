#include "gtest/gtest.h"
#include <functional>
#include <future>
#include <thread>
#include <chrono>

#include "task/Task.h"
#include "logging/VsOutput.h"

namespace Matrix
{
	using std::string;


	Action generateDefaultAction(string name) {
		Action action = [=]() {
			VsOutput::writeWithName("Task", "Start to run task", name);
			VsOutput::debugLine(string(100, '-'));

			for (int i = 0; i < 10; i++)
			{
				VsOutput::writeWithName("Task", "Executing", name, i);
				Task::delay(50)->wait();
			}

			VsOutput::debugLine(string(100, '-'));
			VsOutput::debugLine("");
		};

		return action;
	}
	TEST(TaskTests, IsPrimeCode) {

		std::function isPrime = [](int value) {
			VsOutput::writeWithName("Task", "Start checking", value, "...");
			for (int i = 2; i < value; ++i) {
				if (value%i == 0)
					return false;
			}
			return true;
		};
		int value = 313222313;

		std::future<bool> predicate = std::async(isPrime, value);

		VsOutput::writeWithName("Task", "Checking whether", value, "is prime.");

		bool result = predicate.get();

		VsOutput::writeWithName("Task", value, result ? "is prime." : "is not prime.");

		ASSERT_TRUE(result);
	}

	TEST(TaskTests, ConstructorWithAction) {
		Action action = generateDefaultAction("Simple task");

		Task task(action);

		task.withName("Simple task").start().wait();

		VsOutput::writeWithName("Task", "Task", task.name, "finished");
	}

	TEST(TaskTests, CreateTaskWithRun) {
		Action action = generateDefaultAction("Task from run");
		Task task(action);
		task.withName("Create from run").start().wait();
		VsOutput::writeWithName("Task", "Task", task.name, "finished");
	}

	TEST(TaskTests, WaitAllTasksFinished) {
		Action action1 = generateDefaultAction("Task 1");
		Action action2 = generateDefaultAction("Task 2");
		Action action3 = generateDefaultAction("Task 3");
		Action action4 = generateDefaultAction("Task 4");
		Action action5 = generateDefaultAction("Task 5");

		auto tasks = {
			Task(action1), Task(action2), Task(action3), Task(action4), Task(action5)
		};

		Task::waitAll(tasks);

	}

	TEST(TaskTests, TryDoWithException) {
		int executeCount = 0;

		Action action = [&]() {
			executeCount++;
			if (executeCount < 2)
				throw std::runtime_error("should abort");
		};

		Task::tryDo(action)->wait();

		ASSERT_EQ(executeCount, 2);
	}

	TEST(TaskTests, TryDoWithoutException) {
		int executeCount = 0;

		Action action = [&]() {
			executeCount++;
		};

		Task::tryDo(action)->wait();

		ASSERT_EQ(executeCount, 1);
	}

	TEST(TaskTests, TryDoMax10) {
		int executeCount = 0;

		Action action = [&]() {
			executeCount++;

			throw std::runtime_error("shoul abort");
		};

		Task::tryDo(action, 10, 50)->wait();

		ASSERT_EQ(executeCount, 10);
	}

	TEST(TaskTests, Extecute) {
		int executeCount = 0;

		Action action = [&]() {
			executeCount++;
		};

		Task::execute(action)->wait();

		ASSERT_EQ(executeCount, 1);
	}

	TEST(TaskTests, ActionTest) {
		bool invoked = false;
		Action action = [&]() {
			invoked = true;
		};

		action();

		ASSERT_TRUE(invoked);
	}

	TEST(TaskTests, ActionTTest) {
		bool invoked = false;
		string actual;
		string expected = "test";

		ActionArgs<const string&> action = [&](const string& name) {
			invoked = true;
			actual = name;
		};


		action(expected);

		ASSERT_TRUE(invoked);
		ASSERT_EQ(expected, actual);
	}
}