#include "gtest/gtest.h"
#include "services/DataContext.h"
#include "Rectangle.h"
#include "Circle.h"
#include "di/ServiceContainer.h"

namespace Matrix
{
	using std::string;
	TEST(DataContextTests, Constructor) {
		DataContext context;
	}

	TEST(DataContextTests, ConstructorwithServices) {

		auto services = std::make_shared<ServiceContainer>();

		DataContext context(services);				
	}
	TEST(DataContextTests, GetSetdata) {
		DataContext context;

		context.setProperty<string>("name", "pxi")
			.setProperty<string>("version", "1.0")
			.setProperty<int>("int-value", 200)
			.setProperty<Rectangle>("rect", Rectangle("r", 10, 20))
			.setProperty<Circle>("circle", Circle("c", 15))
			;

		ASSERT_EQ(context.getProperty<string>("name"), "pxi");
		ASSERT_EQ(context.getProperty<string>("version"), "1.0");
		ASSERT_EQ(context.getProperty<int>("int-value"), 200);
		ASSERT_EQ(context.getProperty<Rectangle>("rect").name, "r");
		ASSERT_EQ(context.getProperty<Rectangle>("rect").width, 10);
		ASSERT_EQ(context.getProperty<Rectangle>("rect").height, 20);
		ASSERT_EQ(context.getProperty<Circle>("circle").name, "c");
		ASSERT_EQ(context.getProperty<Circle>("circle").radius, 15);
	}

	TEST(DataContextTests, Clear) {
		DataContext context;

		context.clear();
	}

}