#include <gtest/gtest.h>

#include <cpp-anvil/nbt.hpp>

TEST(ByteTag, Constructor)
{
    nbt::ByteTag byteTag;
    EXPECT_EQ(byteTag.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTag.name(), "");
    EXPECT_EQ(byteTag.value(), 0);
}

TEST(ByteTag, Constructor_Name)
{
    const std::string name = "Some Name";
    nbt::ByteTag byteTag(name);
    EXPECT_EQ(byteTag.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTag.name(), name);
    EXPECT_EQ(byteTag.value(), 0);
}

TEST(ByteTag, Constructor_Value)
{
    const nbt::ByteType value = 0x56;
    nbt::ByteTag byteTag(value);
    EXPECT_EQ(byteTag.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTag.name(), "");
    EXPECT_EQ(byteTag.value(), value);
}

TEST(ByteTag, Constructor_Name_Value)
{
    const std::string name = "Some Other Name";
    const nbt::ByteType value = 0xAB;
    nbt::ByteTag byteTag(name, value);
    EXPECT_EQ(byteTag.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTag.name(), name);
    EXPECT_EQ(byteTag.value(), value);
}

TEST(ByteTag, Constructor_Copy)
{
    const std::string name = "Copy Test";
    const nbt::ByteType value = 0xEF;
    nbt::ByteTag byteTagA(name, value);
    EXPECT_EQ(byteTagA.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTagA.name(), name);
    EXPECT_EQ(byteTagA.value(), value);

    nbt::ByteTag byteTagB(byteTagA);
    EXPECT_EQ(byteTagB.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTagB.name(), name);
    EXPECT_EQ(byteTagB.value(), value);

    EXPECT_EQ(byteTagA, byteTagB);
}

TEST(ByteTag, Constructor_Move)
{
    const std::string name = "Move Test";
    const nbt::ByteType value = 0xEF;
    nbt::ByteTag byteTagA(name, value);
    EXPECT_EQ(byteTagA.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTagA.name(), name);
    EXPECT_EQ(byteTagA.value(), value);

    nbt::ByteTag byteTagB(std::move(byteTagA));
    EXPECT_EQ(byteTagB.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTagB.name(), name);
    EXPECT_EQ(byteTagB.value(), value);

    EXPECT_NE(byteTagA, byteTagB);
}

TEST(ByteTag, Copy_Assign)
{
    const std::string nameA = "TagA";
    const std::string nameB = "TagB";
    const nbt::ByteType valueA = 0xEF;
    const nbt::ByteType valueB = 0xCD;
    nbt::ByteTag byteTagA(nameA, valueA);
    EXPECT_EQ(byteTagA.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTagA.name(), nameA);
    EXPECT_EQ(byteTagA.value(), valueA);

    nbt::ByteTag byteTagB(nameB, valueB);
    EXPECT_EQ(byteTagB.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTagB.name(), nameB);
    EXPECT_EQ(byteTagB.value(), valueB);

    EXPECT_NE(byteTagA, byteTagB);

    byteTagB = byteTagA;
    EXPECT_EQ(byteTagA, byteTagB);
}

TEST(ByteTag, Move_Assign)
{
    const std::string nameA = "TagA";
    const std::string nameB = "TagB";
    const nbt::ByteType valueA = 0xEF;
    const nbt::ByteType valueB = 0xCD;
    nbt::ByteTag byteTagA(nameA, valueA);
    EXPECT_EQ(byteTagA.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTagA.name(), nameA);
    EXPECT_EQ(byteTagA.value(), valueA);

    nbt::ByteTag byteTagB(nameB, valueB);
    EXPECT_EQ(byteTagB.type(), nbt::TagType::Byte);
    EXPECT_EQ(byteTagB.name(), nameB);
    EXPECT_EQ(byteTagB.value(), valueB);

    EXPECT_NE(byteTagA, byteTagB);

    byteTagB = std::move(byteTagA);
    EXPECT_NE(byteTagA, byteTagB);
    EXPECT_EQ(byteTagB.name(), nameA);
    EXPECT_EQ(byteTagB.value(), valueA);
}

TEST(ByteTag, setName)
{
    const std::string name = "TestName";
    nbt::ByteTag byteTag;
    EXPECT_EQ(byteTag.name(), "");
    byteTag.setName(name);
    EXPECT_EQ(byteTag.name(), name);
}

TEST(ByteTag, setValue)
{
    const nbt::ByteType value = 0xAB;
    nbt::ByteTag byteTag;
    EXPECT_EQ(byteTag.value(), 0);
    byteTag.setValue(value);
    EXPECT_EQ(byteTag.value(), value);
}

TEST(ByteTag, Equality)
{
    nbt::ByteTag byteTagA;
    nbt::ByteTag byteTagB;
    EXPECT_TRUE(byteTagA == byteTagA);    // Same object
    EXPECT_TRUE(byteTagA == byteTagB);    // Other object
}

TEST(ByteTag, tag_cast)
{
    const std::string name = "Some Other Name";
    const nbt::ByteType value = 0xAB;
    nbt::BasicTag *byteTag = new nbt::ByteTag(name, value);

    nbt::ByteTag *otherTag = nbt::tag_cast<nbt::ByteTag*>(byteTag);
    EXPECT_EQ(otherTag, byteTag);

    delete byteTag;
}