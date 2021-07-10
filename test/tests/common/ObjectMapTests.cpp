#include "gtest/gtest.h"
#include "common/ObjectMap.h"
#include "Circle.h"

namespace Matrix
{
	using std::string;
	TEST(ObjectMapTests, Constructor) {

		ObjectMap<string> map;
	}
	
	TEST(ObjectMapTests, AddValues) {

		ObjectMap<string> map;
		map.add("int", 20);
		map.add("string", "text value");

		ASSERT_EQ(2, map.size());

		map.clear();

		ASSERT_EQ(0, map.size());
	}

	TEST(ObjectMapTests, GetValues) {
		auto f = std::make_shared<float>(2.16f);
		ASSERT_EQ(2.16f, *f);

		Circle circle("sun", 20);

		ObjectMap<string> map;
		map.add("int", 20)
			.add<string>("string", "text value")
			.add<int>("int-value", 30)
			.add("float", 2.15f)
			.add<double>("double", 3.14)
			.add<Circle>("sun", circle)
			;

		ASSERT_EQ(6, map.size());

		ASSERT_EQ(20, map.getValue<int>("int"));		
		ASSERT_EQ(30, map.getValue<int>("int-value"));
		ASSERT_EQ("text value", map.getValue<string>("string"));
		ASSERT_EQ(2.15f, map.getValue<float>("float"));
		ASSERT_EQ(3.14, map.getValue<double>("double"));
		ASSERT_EQ("sun", map.getValue<Circle>("sun").name);
		ASSERT_EQ(20, map.getValue<Circle>("sun").radius);

		ASSERT_EQ(11, map.getValue<int>("default", 11));
	}

	TEST(ObjectMapTests, AddDuplicated) {

		ObjectMap<string> map;

		map.add("int", 20).add("int", 30);

		ASSERT_EQ(1, map.size());
		ASSERT_EQ(30, map.getValue<int>("int"));
	}

	TEST(ObjectMapTests, Keys) {
		Circle circle("sun", 20);
		ObjectMap<string> map;
		map.add("int", 20)
			.add<string>("string", "text value")
			.add<int>("int-value", 30)
			.add("float", 2.15f)
			.add<double>("double", 3.14)
			.add<Circle>("sun", circle)
			;

		auto keys = map.keys();
		ASSERT_EQ(6, keys.size());
	}
}