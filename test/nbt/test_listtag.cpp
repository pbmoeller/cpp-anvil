#include <gtest/gtest.h>

#include <cpp-anvil/nbt.hpp>

TEST(ListTag, Constructor)
{
    anvil::ListTag listTag;
    EXPECT_EQ(listTag.type(), anvil::TagType::List);
    EXPECT_EQ(listTag.name(), "");
    EXPECT_EQ(listTag.listType(), anvil::TagType::End);
    EXPECT_TRUE(listTag.empty());
    EXPECT_EQ(listTag.size(), 0);
}

TEST(ListTag, Constructor_Name)
{
    const std::string name = "Some Name";

    anvil::ListTag listTag(name);
    EXPECT_EQ(listTag.type(), anvil::TagType::List);
    EXPECT_EQ(listTag.name(), name);
    EXPECT_EQ(listTag.listType(), anvil::TagType::End);
    EXPECT_TRUE(listTag.empty());
    EXPECT_EQ(listTag.size(), 0);
}

TEST(ListTag, Constructor_Value)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ListTag, Constructor_Name_Value)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ListTag, Constructor_Copy)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ListTag, Constructor_Move)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ListTag, Copy_Assign)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ListTag, Move_Assign)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}


TEST(ListTag, push_back)
{
    anvil::ListTag listTag;
    EXPECT_EQ(listTag.type(), anvil::TagType::List);
    EXPECT_EQ(listTag.name(), "");
    EXPECT_EQ(listTag.listType(), anvil::TagType::End);
    EXPECT_TRUE(listTag.empty());
    EXPECT_EQ(listTag.size(), 0);

    auto byteTag = std::make_unique<anvil::ByteTag>(0xAA);

    EXPECT_TRUE(listTag.push_back(std::move(byteTag)));
    EXPECT_EQ(listTag.listType(), anvil::TagType::Byte);
    EXPECT_FALSE(listTag.empty());
    EXPECT_EQ(listTag.size(), 1);

    auto byteTag2 = std::make_unique<anvil::ByteTag>(0xAC);

    EXPECT_TRUE(listTag.push_back(std::move(byteTag2)));
    EXPECT_FALSE(listTag.empty());
    EXPECT_EQ(listTag.size(), 2);

    auto intTag = std::make_unique<anvil::IntTag>(0xACFB1234);
    EXPECT_FALSE(listTag.push_back(std::move(intTag)));
    EXPECT_FALSE(listTag.empty());
    EXPECT_EQ(listTag.size(), 2);
}
