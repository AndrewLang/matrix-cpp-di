#include "gtest/gtest.h"
#include "task/Do.h"

namespace Matrix
{
	TEST(DoTests, Constructor) {
		auto lambda = [](int x) {  };
		Do<std::function<void(int)>> action(lambda);
	}

	TEST(DoTests, SetSleep) {
		auto lambda = [](int x) {};
		Do<std::function<void(int)>> action(lambda);

		action.sleep(100);
	}

	TEST(DoTests, SetAttemp) {
		auto lambda = [](int x) {};
		Do<std::function<void(int)>> action(lambda);

		action.attempt(5);
	}

	TEST(DoTests, Start) {
		int count = 0;
		int actual = 0;
		auto lambda = [&](int x)
		{
			count++;
			if (count < 3)
				throw new std::runtime_error("test exception");

			actual = x;
		};
		Do<std::function<void(int)>> action(lambda);

		action.attempt(3).sleep(100).start(5);

		ASSERT_EQ(3, count);
		ASSERT_EQ(5, actual);
	}

	TEST(DoTests, StartVoid) {
		int count = 0;
		int attempt = 5;
		int actual = 0;
		auto lambda = [&](int x)
		{
			count++;
			if (count < attempt)
				throw new std::runtime_error("test exception");

			actual = x;
		};
		Do<std::function<void(int)>> action(lambda);

		action.attempt(attempt).sleep(100).start(50);

		ASSERT_EQ(attempt, count);
		ASSERT_EQ(50, actual);
	}
}