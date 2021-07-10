#include "gtest/gtest.h"
#include "di/ServiceLifetime.h"
#include "Circle.h"
#include "Rectangle.h"

namespace Matrix
{
	TEST(FactoryTests, SharedInstanceFactoryTest) {
		auto circle1 = sharedInstanceFactory<Circle>();
		auto circle2 = sharedInstanceFactory<Circle>("circle", 20);

		ASSERT_EQ("circle", circle2->name);
		ASSERT_EQ(20, circle2->radius);
	}

	TEST(FactoryTests, UniqueInstanceFactoryTest) {
		auto rect1 = sharedInstanceFactory<Rectangle>();
		auto rect2 = sharedInstanceFactory<Rectangle>("rect", 20, 30);

		ASSERT_EQ("rect", rect2->name);
		ASSERT_EQ(20, rect2->width);
		ASSERT_EQ(30, rect2->height);
	}

	TEST(FactoryTests, ObjectFactoryTest) {
		ObjectFactory factory = DefaultInstanceFactory<Rectangle>();

		auto instance = factory();
		auto rect = std::static_pointer_cast<Rectangle>(instance);
		ASSERT_EQ("Rectangle", rect->name);
	}

	TEST(FactoryTests, GenericFactoryTest) {
		GenericObjectFactory<Rectangle> factory = ParameterInstanceFactory<Rectangle>("rect", 20,30);

		auto instance = factory();
		
		ASSERT_EQ("rect", instance->name);
	}
}