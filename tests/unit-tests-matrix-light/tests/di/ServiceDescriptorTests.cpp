#include "Circle.h"
#include "Rectangle.h"
#include "di/ServiceDescriptor.h"
#include "gtest/gtest.h"

namespace Matrix
{
TEST(ServiceDescriptorTests, Constructor)
{
    ServiceDescriptor descriptor;

    EXPECT_EQ(ServiceLifetime::Singleton, descriptor.lifetime);

    EXPECT_EQ(nullptr, descriptor.instance);
    EXPECT_EQ(nullptr, descriptor.creatorContext);
}

TEST(ServiceDescriptorTests, WithName)
{
    ServiceDescriptor descriptor;

    EXPECT_EQ("", descriptor.alias);

    descriptor.withAlias("test");

    EXPECT_EQ("test", descriptor.alias);
}

TEST(ServiceDescriptorTests, TransientWithDeclare)
{
    auto descriptor = ServiceDescriptor::Transient<Rectangle>();
    auto rectType = TypeInfo::From<Rectangle>();

    EXPECT_EQ(ServiceLifetime::Transient, descriptor->lifetime);
    EXPECT_EQ(rectType->getName(), descriptor->serviceType->getName());
    EXPECT_EQ(rectType->getName(), descriptor->implementationType->getName());

    auto rect = descriptor->getInstance<Rectangle>();
    EXPECT_EQ("Rectangle", rect->name);
}

TEST(ServiceDescriptorTests, TransientWithImplementation)
{
    auto descriptor = ServiceDescriptor::Transient<Shape, Rectangle>();
    auto rectType = TypeInfo::From<Rectangle>();
    auto shapeType = TypeInfo::From<Shape>();

    EXPECT_EQ(ServiceLifetime::Transient, descriptor->lifetime);
    EXPECT_EQ(shapeType->getName(), descriptor->serviceType->getName());
    EXPECT_EQ(rectType->getName(), descriptor->implementationType->getName());

    auto rect = descriptor->getInstance<Shape>();
    EXPECT_EQ("Rectangle", rect->name);

    auto rect1 = descriptor->getInstance<Shape>();

    ASSERT_NE(rect->id, rect1->id);
}

TEST(ServiceDescriptorTests, TransientWithFactory)
{
    auto descriptor = ServiceDescriptor::Transient<Shape, Rectangle>(ParameterInstanceFactory<Rectangle>("rect", 20, 30), "Large");

    auto rectType = TypeInfo::From<Rectangle>();
    auto shapeType = TypeInfo::From<Shape>();

    EXPECT_EQ(ServiceLifetime::Transient, descriptor->lifetime);
    EXPECT_EQ(shapeType->getName(), descriptor->serviceType->getName());
    EXPECT_EQ(rectType->getName(), descriptor->implementationType->getName());
    EXPECT_EQ("Large", descriptor->alias);

    auto rect = descriptor->getInstance<Rectangle>();
    EXPECT_EQ("rect", rect->name);
    EXPECT_EQ(20, rect->width);
    EXPECT_EQ(30, rect->height);

    auto rect1 = descriptor->getInstance<Shape>();
    ASSERT_NE(rect->id, rect1->id);
}

TEST(ServiceDescriptorTests, TransientWithCreatorContext)
{

    // InstanceCreatorContext context;
    auto descriptor = ServiceDescriptor::Transient<Shape, Rectangle>(ParameterInstanceFactory<Rectangle>("rect", 20, 30), "Large");
    auto rectType = TypeInfo::From<Rectangle>();
    auto shapeType = TypeInfo::From<Shape>();

    EXPECT_EQ(ServiceLifetime::Transient, descriptor->lifetime);
    EXPECT_EQ(shapeType->getName(), descriptor->serviceType->getName());
    EXPECT_EQ(rectType->getName(), descriptor->implementationType->getName());
    EXPECT_EQ("Large", descriptor->alias);

    auto rect = descriptor->getInstance<Rectangle>();
    EXPECT_EQ("rect", rect->name);
    EXPECT_EQ(20, rect->width);
    EXPECT_EQ(30, rect->height);

    auto rect1 = descriptor->getInstance<Shape>();
    ASSERT_NE(rect->id, rect1->id);
}

TEST(ServiceDescriptorTests, SingletonWithDeclare)
{
    auto descriptor = ServiceDescriptor::Singleton<Rectangle>();
    auto rectType = TypeInfo::From<Rectangle>();

    EXPECT_EQ(ServiceLifetime::Singleton, descriptor->lifetime);
    EXPECT_EQ(rectType->getName(), descriptor->serviceType->getName());
    EXPECT_EQ(rectType->getName(), descriptor->implementationType->getName());

    auto rect = descriptor->getInstance<Rectangle>();
    EXPECT_EQ("Rectangle", rect->name);
}

TEST(ServiceDescriptorTests, SingletonWithImplementation)
{
    auto descriptor = ServiceDescriptor::Singleton<Shape, Rectangle>();
    auto rectType = TypeInfo::From<Rectangle>();
    auto shapeType = TypeInfo::From<Shape>();

    EXPECT_EQ(ServiceLifetime::Singleton, descriptor->lifetime);
    EXPECT_EQ(shapeType->getName(), descriptor->serviceType->getName());
    EXPECT_EQ(rectType->getName(), descriptor->implementationType->getName());

    auto rect = descriptor->getInstance<Shape>();
    EXPECT_EQ("Rectangle", rect->name);

    auto rect1 = descriptor->getInstance<Shape>();

    EXPECT_EQ(rect->id, rect1->id);
}

TEST(ServiceDescriptorTests, SingletonWithFactory)
{
    auto descriptor = ServiceDescriptor::Singleton<Shape, Rectangle>(ParameterInstanceFactory<Rectangle>("rect", 20, 30), "Large");
    auto rectType = TypeInfo::From<Rectangle>();
    auto shapeType = TypeInfo::From<Shape>();

    EXPECT_EQ(ServiceLifetime::Singleton, descriptor->lifetime);
    EXPECT_EQ(shapeType->getName(), descriptor->serviceType->getName());
    EXPECT_EQ(rectType->getName(), descriptor->implementationType->getName());
    EXPECT_EQ("Large", descriptor->alias);

    auto rect = descriptor->getInstance<Rectangle>();
    EXPECT_EQ("rect", rect->name);
    EXPECT_EQ(20, rect->width);
    EXPECT_EQ(30, rect->height);

    auto rect1 = descriptor->getInstance<Shape>();
    EXPECT_EQ(rect->id, rect1->id);
}

TEST(ServiceDescriptorTests, SingletonWithCreatorContext)
{

    // InstanceCreatorContext context;
    auto descriptor = ServiceDescriptor::Singleton<Shape, Rectangle>(ParameterInstanceFactory<Rectangle>("rect", 20, 30), "Large");
    auto rectType = TypeInfo::From<Rectangle>();
    auto shapeType = TypeInfo::From<Shape>();

    EXPECT_EQ(ServiceLifetime::Singleton, descriptor->lifetime);
    EXPECT_EQ(shapeType->getName(), descriptor->serviceType->getName());
    EXPECT_EQ(rectType->getName(), descriptor->implementationType->getName());
    EXPECT_EQ("Large", descriptor->alias);

    auto rect = descriptor->getInstance<Rectangle>();
    EXPECT_EQ("rect", rect->name);
    EXPECT_EQ(20, rect->width);
    EXPECT_EQ(30, rect->height);

    auto rect1 = descriptor->getInstance<Shape>();
    EXPECT_EQ(rect->id, rect1->id);
}
} // namespace Matrix
