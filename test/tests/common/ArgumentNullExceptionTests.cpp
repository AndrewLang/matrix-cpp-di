#include "gtest/gtest.h"
#include "common/ArgumentNullException.h"

namespace Matrix
{
	TEST(ArgumentNullExceptionTests, Constructor) {
		ArgumentNullException exception("test");

		ASSERT_EQ("test", exception.getArgument());
	}

}