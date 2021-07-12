#include "gtest/gtest.h"
#include "common/Guard.h"
#include <stdio.h>

namespace Matrix
{
	TEST(GuardTests, NotNull) {
		EXPECT_ANY_THROW(
			Guard::notNull(nullptr, "test");
		);
	}

	TEST(GuardTests, NotEmpty) {
		EXPECT_ANY_THROW(
			Guard::notEmpty("", "test");
		);
	}

	TEST(GuardTests, PrintFormat) {
		printf("Characters: %c %c %s \n", 'a', 65, "");
		printf("%s %s\n", "A string" , "");
	}
}