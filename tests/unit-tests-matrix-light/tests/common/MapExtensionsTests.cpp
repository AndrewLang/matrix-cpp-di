#include "gtest/gtest.h"
#include "common/MapExtensions.h"
#include "Rectangle.h"

namespace Matrix
{
	using namespace std;

	TEST(MapExtensionsTests, Get)
	{
		map<int, string> map = {
			{1, "slot1"},
			{2, "slot2"}
		};

		auto actual = Maps::get<int, string>(map, 1);
		ASSERT_EQ(actual, "slot1");
	}
}