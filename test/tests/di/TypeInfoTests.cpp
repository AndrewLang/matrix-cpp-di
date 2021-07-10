#include "gtest/gtest.h"
#include "di/TypeInfo.h"

namespace Matrix
{
	TEST(TypeInfoTests, Constructor) {
		TypeInfo info(&typeid(int));

		auto expect = &typeid(int);

		ASSERT_EQ(expect, info.rawType);

		#if defined(_WIN32)
		ASSERT_EQ("int", info.name);
		#else
		ASSERT_EQ("i", info.name);
		#endif
	}

	TEST(TypeInfoTests, FromGeneric) {
		auto info = TypeInfo::From<int>();

		auto expect = &typeid(int);

		ASSERT_EQ(expect, info->rawType);
		
		#if defined(_WIN32)
		ASSERT_EQ("int", info->name);
		#else
		ASSERT_EQ("i", info->name);
		#endif
	}

	TEST(TypeInfoTests, EqualsOperation) {
		TypeInfo info = &typeid(int);

		auto expect = &typeid(int);

		ASSERT_EQ(expect, info.rawType);
		
		#if defined(_WIN32)
		ASSERT_EQ("int", info.name);
		#else
		ASSERT_EQ("i", info.name);
		#endif
	}
}