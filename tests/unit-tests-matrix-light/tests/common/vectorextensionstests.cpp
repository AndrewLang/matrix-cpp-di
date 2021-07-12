#include "gtest/gtest.h"
#include "common/VectorExtensions.h"
#include "Rectangle.h"

namespace Matrix
{
	using namespace std;

	TEST(VectorExtensionsTests, FirstOrDefault) {
		vector<int> values = { 1,3,5,7,9 };
		function predicate = [](int x) {
			return x == 7;
		};
		int expect = Vectors::firstOrDefault(values, predicate);

		ASSERT_EQ(7, expect);

		expect = Vectors::firstOrDefault<int>(values, [](int x) { return x == 7; });

		ASSERT_EQ(7, expect);
	}

	TEST(VectorExtensionsTests, FirstOrDefaultWithObject) {
		vector<Rectangle> rectangles = {
		 Rectangle("rect", 200, 100),
		 Rectangle("square", 200, 200)
		};

		auto expect = Vectors::firstOrDefault<Rectangle>(rectangles, [](Rectangle rect) {
			return rect.name == "rect";
			});

		ASSERT_EQ(expect.width, 200);
		ASSERT_EQ(expect.height, 100);
	}

	TEST(VectorExtensionsTests, Foreach) {
		vector<int> values = { 1,3,5,7,9 };

		int sum = 0;
		Vectors::foreach<int>(values, [&](int x) {
			sum += x;
			});
		ASSERT_EQ(sum, 25);
	}

	TEST(VectorExtensionsTests, Where) {
		vector<int> values = { 1,3,5,7,9,10 };

		auto expect = Vectors::where<int>(values, [](int x) {
			return x % 2 == 0;
			});

		ASSERT_EQ(expect.size(), 1);
		ASSERT_EQ(expect[0], 10);
	}

	TEST(VectorExtensionsTests, Merge) {
		vector<int> source = { 1,3,5,7,9 };
		vector<int> dest = { 2,4,6,8 };

		auto actual = Vectors::merge(source, dest);

		ASSERT_EQ(actual.size(), 9);
		ASSERT_EQ(source.size(), 9);
		ASSERT_EQ(dest.size(), 4);
	}

	TEST(VectorExtensionsTests, Any) {
		vector<int> source = { 1,3,5,7,9 };

		auto actual = Vectors::any<int>(source, [](int value) {
			return value == 7;
			});

		ASSERT_TRUE(actual);
	}

	TEST(VectorExtensionsTests, IsEmpty) {
		vector<int> source = { 1,3,5,7,9 };
		vector<int> empty;

		ASSERT_TRUE(Vectors::isEmpty(empty));
		ASSERT_FALSE(Vectors::isEmpty(source));
	}

	TEST(VectorExtensionsTests, NotEmpty) {
		vector<int> source = { 1,3,5,7,9 };
		vector<int> empty;

		ASSERT_TRUE(Vectors::notEmpty(source));
		ASSERT_FALSE(Vectors::notEmpty(empty));
	}

	TEST(VectorExtensionsTests, Join) {
		vector<int> source = { 1,3,5,7,9 };

		auto actual = Vectors::join(source);
		ASSERT_EQ(actual, "13579");

		auto actual1 = Vectors::join(source, ",");
		ASSERT_EQ(actual1, "1,3,5,7,9");

		vector<string> values = { "1", "2" };
		auto actual2 = Vectors::join(values, ",");
		ASSERT_EQ(actual2, "1,2");
	}

	TEST(VectorExtensionsTests, SelectAll) {
		Rectangle rect1;	
        rect1.addChild(Rectangle());
        rect1.addChild(Rectangle());
        rect1.addChild(Rectangle());

        Rectangle rect2;
        rect2.addChild(Rectangle());
        rect2.addChild(Rectangle());
        rect2.addChild(Rectangle());

		vector<Rectangle> rects = { rect1, rect2 };

        auto children = Vectors::selectAll<Rectangle, Rectangle>(rects, [](Rectangle rect) { return rect.children(); });

        EXPECT_EQ(6, children.size());
	}

	TEST(VectorExtensionsTests, Range) {

		vector<int> source = { 1,3,5,7,9,11,13,15,17,19 };

		auto actual = Vectors::range(source, 0, 3);
		ASSERT_EQ(3, actual.size());
		ASSERT_EQ(1, actual[0]);
		ASSERT_EQ(3, actual[1]);
		ASSERT_EQ(5, actual[2]);

		actual = Vectors::range(source, source.size() + 1, 3);
		ASSERT_EQ(0, actual.size());

		actual = Vectors::range(source, 3, 4);
		ASSERT_EQ(4, actual.size());
		ASSERT_EQ(7, actual[0]);
		ASSERT_EQ(9, actual[1]);
		ASSERT_EQ(11, actual[2]);
		ASSERT_EQ(13, actual[3]);
	}

	TEST(VectorExtensionsTests, Fill) {
		vector<int> source = { };
		Vectors::fill(source, 1, 10);

		ASSERT_EQ(10, source.size());
		ASSERT_EQ(1, source[0]);
		ASSERT_EQ(1, source[9]);
	}
}