#include "gtest/gtest.h"
#include "di/ServiceContainer.h"
#include "di/ServiceDescriptor.h"
#include "di/TypeInfo.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Shape.h"


namespace Matrix
{
	TEST(ServiceContainerTests, Constructor) {
		ServiceContainer container;
	}

	TEST(ServiceContainerTests, RegisterService) {
		ServiceContainer container;
		auto rectDescriptor = ServiceDescriptor::Singleton<Shape, Rectangle>();
		auto circleDescriptor = ServiceDescriptor::Transient<Circle>();

		container.registerService(rectDescriptor)
			.registerService(circleDescriptor);
	}

	TEST(ServiceContainerTests, GetService) {
		ServiceContainer container;
		auto rectDescriptor = ServiceDescriptor::Singleton<Shape, Rectangle>();
		auto circleDescriptor = ServiceDescriptor::Transient<Circle>();

		container.registerService(rectDescriptor)
			.registerService(circleDescriptor);

		auto rect = std::static_pointer_cast<Rectangle>(container.getService(TypeInfo::From<Shape>()));

		ASSERT_EQ("Rectangle", rect->name);

		auto circle = std::static_pointer_cast<Circle>(container.getService(TypeInfo::From<Circle>()));

		ASSERT_EQ("Circle", circle->name);
	}

	TEST(ServiceContainerTests, TransientWithDeclare) {
		ServiceContainer container;
		container.transient<Rectangle>()
			.transient<Shape, Circle>();

		auto rect1 = container.resolveService<Rectangle>();
		auto rect2 = container.resolveService<Rectangle>();

		ASSERT_NE(rect1->id, rect2->id);

		auto circle1 = container.resolveService<Shape>();
		auto circle2 = container.resolveService<Shape>();

		ASSERT_NE(circle1->id, circle2->id);
	}

	TEST(ServiceContainerTests, TransientWithFactory) {
		ServiceContainer container;

		container
			.transient<Circle>(ParameterInstanceFactory<Circle>("circle", 20))
			.transient<Shape, Rectangle>(ParameterInstanceFactory<Rectangle>("rect", 20, 30), "RandomRect");

		auto rect1 = container.resolveService<Shape>();
		auto rect2 = container.resolveService<Shape>();

		auto circle1 = container.resolveService<Circle>();
		auto circle2 = container.resolveService<Circle>();

		ASSERT_NE(rect1->id, rect2->id);
		ASSERT_NE(circle1->id, circle2->id);

		ASSERT_EQ(20, circle1->radius);
		ASSERT_EQ(20, circle2->radius);

		ASSERT_EQ("rect", rect1->name);
		ASSERT_EQ("rect", rect2->name);
	}

	TEST(ServiceContainerTests, TransientWithParameterFactory) {
		ServiceContainer container;

		container.transient<Shape, Rectangle>([](IServiceProvider* serviceProvider) {
			return ParameterInstanceFactory<Rectangle>("rect", 20, 30);	});

		auto rect1 = container.resolveService<Shape>();
		auto rect2 = container.resolveService<Shape>();

		ASSERT_NE(rect1->id, rect2->id);

		ASSERT_EQ("rect", rect1->name);
		ASSERT_EQ("rect", rect2->name);
	}

	TEST(ServiceContainerTests, SingletonWithDeclare) {
		ServiceContainer container;
		container.singleton<Rectangle>()
			.singleton<Shape, Circle>();

		auto rect1 = container.resolveService<Rectangle>();
		auto rect2 = container.resolveService<Rectangle>();

		ASSERT_EQ(rect1->id, rect2->id);

		auto circle1 = container.resolveService<Shape>();
		auto circle2 = container.resolveService<Shape>();

		ASSERT_EQ(circle1->id, circle2->id);
	}

	TEST(ServiceContainerTests, SingletonWithName) {
		ServiceContainer container;
		container
			.singleton<Shape, Rectangle>(ParameterInstanceFactory<Rectangle>("r1", 20, 30), "r1")
			.singleton<Shape, Rectangle>(ParameterInstanceFactory<Rectangle>("r2", 40, 50), "r2");


		auto s1 = container.resolveService<Shape>("r1");

		ASSERT_EQ("r1", s1->name);
		
		auto s2 = container.resolveService<Shape>("r2");

		ASSERT_EQ("r2", s2->name);

		auto r2 = std::static_pointer_cast<Rectangle>(s2);

		
		ASSERT_EQ("r2", r2->name);
		ASSERT_EQ(40, r2->width);
		ASSERT_EQ(50, r2->height);
	}
	TEST(ServiceContainerTests, SingletonWithFactory) {
		ServiceContainer container;

		container
			.singleton<Circle>(ParameterInstanceFactory<Circle>("circle", 20))
			.singleton<Shape, Rectangle>(ParameterInstanceFactory<Rectangle>("rect", 20, 30), "RandomRect")
			;

		auto rect1 = container.resolveService<Shape>();
		auto rect2 = container.resolveService<Shape>();

		auto circle1 = container.resolveService<Circle>();
		auto circle2 = container.resolveService<Circle>();

		ASSERT_EQ(rect1->id, rect2->id);
		ASSERT_EQ(circle1->id, circle2->id);

		ASSERT_EQ(20, circle1->radius);
		ASSERT_EQ(20, circle2->radius);

		ASSERT_EQ("rect", rect1->name);
		ASSERT_EQ("rect", rect2->name);
	}

	TEST(ServiceContainerTests, SingletonWithParameterFactory) {
		ServiceContainer container;

		container.singleton<Shape, Rectangle>([](IServiceProvider* serviceProvider) {
			return ParameterInstanceFactory<Rectangle>("rect", 20, 30);	});

		auto rect1 = container.resolveService<Shape>();
		auto rect2 = container.resolveService<Shape>();

		ASSERT_EQ(rect1->id, rect2->id);

		ASSERT_EQ("rect", rect1->name);
		ASSERT_EQ("rect", rect2->name);
	}

	TEST(ServiceContainerTests, RegisterInstance) {
		ServiceContainer container;

		auto rect = std::make_shared<Rectangle>("rect", 20, 30);

		container
			.instance<Rectangle>(rect)
			.instance<Shape>(std::make_shared<Circle>("circle", 25))
			;

		auto rect1 = container.resolveService<Rectangle>();
		auto rect2 = container.resolveService<Rectangle>();

		ASSERT_EQ(rect1->id, rect2->id);

		auto circle1 = container.resolveService<Shape>();
		auto circle2 = container.resolveService<Shape>();

		ASSERT_EQ(circle1->id, circle2->id);
	}
}