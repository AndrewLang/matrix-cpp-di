#include "gtest/gtest.h"
#include "di/TypeMap.h"

namespace Matrix
{
	TEST(TypeMapTests, Constructor) {
		TypeMap<int> map1;
		TypeMap<std::string> map2;
	}

	TEST(TypeMapTests, AddGet) {
		TypeMap<int> intMap;
		intMap.add(TypeInfo::From<int>(), 1);
		intMap.add(TypeInfo::From<std::string>(), 2);

		ASSERT_EQ(2, intMap.size());

		auto intType = TypeInfo::From<int>();
		auto stringType = TypeInfo::From<std::string>();

		ASSERT_TRUE(intMap.contains(intType));
		ASSERT_TRUE(intMap.contains(stringType));

		ASSERT_EQ(1, intMap.get(intType));
		ASSERT_EQ(2, intMap.get(stringType));

		TypeMap<std::string> stringMap;
		stringMap.add(TypeInfo::From<int>(), "int");
		stringMap.add(TypeInfo::From<std::string>(), "string");

		ASSERT_EQ(2, stringMap.size());

		ASSERT_TRUE(stringMap.contains(intType));
		ASSERT_TRUE(stringMap.contains(stringType));

		ASSERT_EQ("int", stringMap.get(intType));
		ASSERT_EQ("string", stringMap.get(stringType));
	}
}