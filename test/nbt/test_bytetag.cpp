#include <gtest/gtest.h>

#include <cpp-anvil/nbt.hpp>

TEST(ByteTag, Constructor)
{
    anvil::ByteTag byteTag;
    EXPECT_EQ(byteTag.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTag.name(), "");
    EXPECT_EQ(byteTag.value(), 0);
}

TEST(ByteTag, Constructor_Name)
{
    const std::string name = "Some Name";
    anvil::ByteTag byteTag(name);
    EXPECT_EQ(byteTag.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTag.name(), name);
    EXPECT_EQ(byteTag.value(), 0);
}

TEST(ByteTag, Constructor_Value)
{
    const anvil::ByteType value = 0x56;
    anvil::ByteTag byteTag(value);
    EXPECT_EQ(byteTag.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTag.name(), "");
    EXPECT_EQ(byteTag.value(), value);
}

TEST(ByteTag, Constructor_Name_Value)
{
    const std::string name      = "Some Other Name";
    const anvil::ByteType value = 0xAB;
    anvil::ByteTag byteTag(name, value);
    EXPECT_EQ(byteTag.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTag.name(), name);
    EXPECT_EQ(byteTag.value(), value);
}

TEST(ByteTag, Constructor_Copy)
{
    const std::string name      = "Copy Test";
    const anvil::ByteType value = 0xEF;
    anvil::ByteTag byteTagA(name, value);
    EXPECT_EQ(byteTagA.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTagA.name(), name);
    EXPECT_EQ(byteTagA.value(), value);

    anvil::ByteTag byteTagB(byteTagA);
    EXPECT_EQ(byteTagB.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTagB.name(), name);
    EXPECT_EQ(byteTagB.value(), value);

    EXPECT_EQ(byteTagA, byteTagB);
}

TEST(ByteTag, Constructor_Move)
{
    const std::string name      = "Move Test";
    const anvil::ByteType value = 0xEF;
    anvil::ByteTag byteTagA(name, value);
    EXPECT_EQ(byteTagA.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTagA.name(), name);
    EXPECT_EQ(byteTagA.value(), value);

    anvil::ByteTag byteTagB(std::move(byteTagA));
    EXPECT_EQ(byteTagB.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTagB.name(), name);
    EXPECT_EQ(byteTagB.value(), value);

    EXPECT_NE(byteTagA, byteTagB);
}

TEST(ByteTag, Copy_Assign)
{
    const std::string nameA      = "TagA";
    const std::string nameB      = "TagB";
    const anvil::ByteType valueA = 0xEF;
    const anvil::ByteType valueB = 0xCD;
    anvil::ByteTag byteTagA(nameA, valueA);
    EXPECT_EQ(byteTagA.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTagA.name(), nameA);
    EXPECT_EQ(byteTagA.value(), valueA);

    anvil::ByteTag byteTagB(nameB, valueB);
    EXPECT_EQ(byteTagB.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTagB.name(), nameB);
    EXPECT_EQ(byteTagB.value(), valueB);

    EXPECT_NE(byteTagA, byteTagB);

    byteTagB = byteTagA;
    EXPECT_EQ(byteTagA, byteTagB);
}

TEST(ByteTag, Move_Assign)
{
    const std::string nameA      = "TagA";
    const std::string nameB      = "TagB";
    const anvil::ByteType valueA = 0xEF;
    const anvil::ByteType valueB = 0xCD;
    anvil::ByteTag byteTagA(nameA, valueA);
    EXPECT_EQ(byteTagA.type(), anvil::TagType::Byte);
    EXPECT_EQ(byteTagA.name(), nameA);
    EXPECT_EQ(byteTagA.value(), valueA);

    anvil::ByteTag byteTagB(nameB, valueB);
    EXPECT_EQ(byteTagB.type(), anvil::TagType::Byte);
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
    anvil::ByteTag byteTag;
    EXPECT_EQ(byteTag.name(), "");
    byteTag.setName(name);
    EXPECT_EQ(byteTag.name(), name);
}

TEST(ByteTag, setValue)
{
    const anvil::ByteType value = 0xAB;
    anvil::ByteTag byteTag;
    EXPECT_EQ(byteTag.value(), 0);
    byteTag.setValue(value);
    EXPECT_EQ(byteTag.value(), value);
}

TEST(ByteTag, Equality)
{
    anvil::ByteTag byteTagA;
    anvil::ByteTag byteTagB;
    EXPECT_TRUE(byteTagA == byteTagA); // Same object
    EXPECT_TRUE(byteTagA == byteTagB); // Other object
}

TEST(ByteTag, tag_cast)
{
    const std::string name      = "Some Other Name";
    const anvil::ByteType value = 0xAB;
    anvil::BasicTag* byteTag    = new anvil::ByteTag(name, value);

    auto* otherTag = anvil::tag_cast<anvil::ByteTag*>(byteTag);
    EXPECT_EQ(otherTag, byteTag);

    delete byteTag;
}
