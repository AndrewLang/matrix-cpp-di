#include "gtest/gtest.h"
#include "task/DoWithResult.h"

namespace Matrix
{
	TEST(DoWithResultTests, Constructor) {
		auto lambda = [](int x) {return x; };
		DoWithResult<int, std::function<int(int)>> action(lambda);
	}

	TEST(DoWithResultTests, SetSleep) {
		auto lambda = [](int x) {return x; };
		DoWithResult<int, std::function<int(int)>> action(lambda);

		action.sleep(100);
	}

	TEST(DoWithResultTests, SetAttemp) {
		auto lambda = [](int x) {return x; };
		DoWithResult<int, std::function<int(int)>> action(lambda);

		action.attempt(5);
	}

	TEST(DoWithResultTests, Start) {
		int count = 0;
		auto lambda = [&](int x) 
		{
			count++;
			if (count < 3)
				throw new std::runtime_error("test exception");

			return x; 
		};
		DoWithResult<int, std::function<int(int)>> action(lambda);

		int actual = action.attempt(3).sleep(100).start(5);

		ASSERT_EQ(3, count);
		ASSERT_EQ(5, actual);
	}

	TEST(DoWithResultTests, StartVoid) {
		int count = 0;
		int attempt = 5;
		auto lambda = [&](int x)
		{
			count++;
			if (count < attempt)
				throw new std::runtime_error("test exception");

			return x;
		};
		DoWithResult<int, std::function<int(int)>> action(lambda);

		int actual = action.attempt(attempt).sleep(100).start(50);

		ASSERT_EQ(attempt, count);
		ASSERT_EQ(50, actual);
	}
}