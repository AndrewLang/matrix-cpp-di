#include "IMessageService.h"
#include "MessageService.h"
#include "Rectangle.h"
#include "di/TypeInfo.h"

#include "gtest/gtest.h"

namespace Matrix
{
TEST(TypeInfoTests, Constructor)
{
    TypeInfo info(&typeid(int));

    auto const expect = &typeid(int);

    EXPECT_EQ(expect->name(), info.getRawType().name());

#if defined(_WIN32)
    EXPECT_EQ("int", info.getName());
#else
    EXPECT_EQ("i", info.getName());
#endif
}

TEST(TypeInfoTests, FromGeneric)
{
    auto info = TypeInfo::From<int>();

    auto expect = &typeid(int);

    EXPECT_EQ(expect->name(), info->getRawType().name());

#if defined(_WIN32)
    EXPECT_EQ("int", info->getName());
#else
    EXPECT_EQ("i", info->getName());
#endif

    auto rectInfo = TypeInfo::From<Rectangle>();
    EXPECT_EQ("Rectangle", rectInfo->getName());

    auto messageService = TypeInfo::From<IMessageService>();
    EXPECT_EQ("Matrix.IMessageService", messageService->getName());

    messageService = TypeInfo::From<MessageService>();
    EXPECT_EQ("Matrix.MessageService", messageService->getName());
}

TEST(TypeInfoTests, EqualsOperation)
{
    auto info = TypeInfo::From<int>();

    auto expect = &typeid(int);

    EXPECT_EQ(expect->name(), info->getRawType().name());

#if defined(_WIN32)
    EXPECT_EQ("int", info->getName());
#else
    EXPECT_EQ("i", info.getName());
#endif
}
} // namespace Matrix
