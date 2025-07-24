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

TEST(ListTag, indexOf)
{
    anvil::ListTag listTag;

    std::unique_ptr<anvil::ByteTag> b1 = std::make_unique<anvil::ByteTag>(2);
    std::unique_ptr<anvil::ByteTag> b2 = std::make_unique<anvil::ByteTag>(2);
    std::unique_ptr<anvil::ByteTag> b3 = std::make_unique<anvil::ByteTag>(2);

    anvil::ByteTag* b1_ptr = b1.get();
    anvil::ByteTag* b2_ptr = b2.get();
    anvil::ByteTag* b3_ptr = b3.get();

    listTag.push_back(std::move(b1));
    listTag.push_back(std::move(b2));
    listTag.push_back(std::move(b3));

    EXPECT_EQ(listTag.size(), 3);

    EXPECT_EQ(listTag.indexOf(b1_ptr), 0);
    EXPECT_EQ(listTag.indexOf(b2_ptr), 1);
    EXPECT_EQ(listTag.indexOf(b3_ptr), 2);
}

TEST(ListTag, takeAt)
{
    anvil::ListTag listTag;

    std::unique_ptr<anvil::ByteTag> b1 = std::make_unique<anvil::ByteTag>("ByteTag", 2);

    anvil::ByteTag* b1_ptr = b1.get();

    listTag.push_back(std::move(b1));
    ASSERT_EQ(listTag.size(), 1);
    ASSERT_EQ(listTag.indexOf(b1_ptr), 0);

    std::unique_ptr<anvil::BasicTag> b1_take = listTag.takeAt(0);
    EXPECT_EQ(listTag.size(), 0);
    EXPECT_EQ(b1_take->type(), anvil::TagType::Byte);
    EXPECT_STREQ(b1_take->name().c_str(), "ByteTag");
}

TEST(ListTag, take)
{
    anvil::ListTag listTag;

    std::unique_ptr<anvil::ByteTag> b1 = std::make_unique<anvil::ByteTag>("ByteTag", 2);

    anvil::ByteTag* b1_ptr = b1.get();

    listTag.push_back(std::move(b1));
    ASSERT_EQ(listTag.size(), 1);
    ASSERT_EQ(listTag.indexOf(b1_ptr), 0);

    std::unique_ptr<anvil::BasicTag> b1_take = listTag.take(b1_ptr);
    EXPECT_EQ(listTag.size(), 0);
    EXPECT_EQ(b1_take->type(), anvil::TagType::Byte);
    EXPECT_STREQ(b1_take->name().c_str(), "ByteTag");
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
