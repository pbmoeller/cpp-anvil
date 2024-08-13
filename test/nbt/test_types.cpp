#include <gtest/gtest.h>

#include <cpp-anvil/nbt.hpp>

TEST(TagType, Types)
{
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::End),        0);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::Byte),       1);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::Short),      2);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::Int),        3);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::Long),       4);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::Float),      5);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::Double),     6);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::ByteArray),  7);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::String),     8);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::List),       9);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::Compound),   10);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::IntArray),   11);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::LongArray),  12);
    EXPECT_EQ(static_cast<unsigned char>(anvil::TagType::Unknown),    255);
}

TEST(TagType, isPrimitiveTag)
{
    EXPECT_FALSE(anvil::isPrimitiveTag(anvil::TagType::End));
    EXPECT_TRUE(anvil::isPrimitiveTag(anvil::TagType::Byte));
    EXPECT_TRUE(anvil::isPrimitiveTag(anvil::TagType::Short));
    EXPECT_TRUE(anvil::isPrimitiveTag(anvil::TagType::Int));
    EXPECT_TRUE(anvil::isPrimitiveTag(anvil::TagType::Long));
    EXPECT_TRUE(anvil::isPrimitiveTag(anvil::TagType::Float));
    EXPECT_TRUE(anvil::isPrimitiveTag(anvil::TagType::Double));
    EXPECT_FALSE(anvil::isPrimitiveTag(anvil::TagType::ByteArray));
    EXPECT_TRUE(anvil::isPrimitiveTag(anvil::TagType::String));
    EXPECT_FALSE(anvil::isPrimitiveTag(anvil::TagType::List));
    EXPECT_FALSE(anvil::isPrimitiveTag(anvil::TagType::Compound));
    EXPECT_FALSE(anvil::isPrimitiveTag(anvil::TagType::IntArray));
    EXPECT_FALSE(anvil::isPrimitiveTag(anvil::TagType::LongArray));
    EXPECT_FALSE(anvil::isPrimitiveTag(anvil::TagType::Unknown));
}

TEST(TagType, isArrayTag)
{
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::End));
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::Byte));
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::Short));
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::Int));
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::Long));
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::Float));
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::Double));
    EXPECT_TRUE(anvil::isArrayTag(anvil::TagType::ByteArray));
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::String));
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::List));
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::Compound));
    EXPECT_TRUE(anvil::isArrayTag(anvil::TagType::IntArray));
    EXPECT_TRUE(anvil::isArrayTag(anvil::TagType::LongArray));
    EXPECT_FALSE(anvil::isArrayTag(anvil::TagType::Unknown));
}

TEST(TagType, isContainerTag)
{
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::End));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::Byte));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::Short));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::Int));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::Long));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::Float));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::Double));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::ByteArray));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::String));
    EXPECT_TRUE(anvil::isContainerTag(anvil::TagType::List));
    EXPECT_TRUE(anvil::isContainerTag(anvil::TagType::Compound));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::IntArray));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::LongArray));
    EXPECT_FALSE(anvil::isContainerTag(anvil::TagType::Unknown));
}

TEST(TagType, isCollectionTag)
{
    EXPECT_FALSE(anvil::isCollectionTag(anvil::TagType::End));
    EXPECT_FALSE(anvil::isCollectionTag(anvil::TagType::Byte));
    EXPECT_FALSE(anvil::isCollectionTag(anvil::TagType::Short));
    EXPECT_FALSE(anvil::isCollectionTag(anvil::TagType::Int));
    EXPECT_FALSE(anvil::isCollectionTag(anvil::TagType::Long));
    EXPECT_FALSE(anvil::isCollectionTag(anvil::TagType::Float));
    EXPECT_FALSE(anvil::isCollectionTag(anvil::TagType::Double));
    EXPECT_TRUE(anvil::isCollectionTag(anvil::TagType::ByteArray));
    EXPECT_FALSE(anvil::isCollectionTag(anvil::TagType::String));
    EXPECT_TRUE(anvil::isCollectionTag(anvil::TagType::List));
    EXPECT_TRUE(anvil::isCollectionTag(anvil::TagType::Compound));
    EXPECT_TRUE(anvil::isCollectionTag(anvil::TagType::IntArray));
    EXPECT_TRUE(anvil::isCollectionTag(anvil::TagType::LongArray));
    EXPECT_FALSE(anvil::isCollectionTag(anvil::TagType::Unknown));
}

TEST(TagType, isValueTag)
{
    EXPECT_FALSE(anvil::isValueTag(anvil::TagType::End));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::Byte));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::Short));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::Int));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::Long));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::Float));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::Double));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::ByteArray));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::String));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::List));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::Compound));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::IntArray));
    EXPECT_TRUE(anvil::isValueTag(anvil::TagType::LongArray));
    EXPECT_FALSE(anvil::isValueTag(anvil::TagType::Unknown));
}

TEST(TagType, isValidTag)
{
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::End));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::Byte));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::Short));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::Int));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::Long));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::Float));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::Double));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::ByteArray));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::String));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::List));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::Compound));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::IntArray));
    EXPECT_TRUE(anvil::isValidTag(anvil::TagType::LongArray));
    EXPECT_FALSE(anvil::isValidTag(anvil::TagType::Unknown));
}

TEST(TagType, getTagTypeName)
{
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::End),       "End");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::Byte),      "Byte");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::Short),     "Short");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::Int),       "Int");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::Long),      "Long");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::Float),     "Float");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::Double),    "Double");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::ByteArray), "ByteArray");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::String),    "String");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::List),      "List");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::Compound),  "Compound");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::IntArray),  "IntArray");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::LongArray), "LongArray");
    EXPECT_EQ(anvil::getTagTypeName(anvil::TagType::Unknown),   "Unknown");
}

TEST(TagType, getTagName)
{
    EXPECT_EQ(anvil::getTagName(anvil::TagType::End),       "EndTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::Byte),      "ByteTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::Short),     "ShortTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::Int),       "IntTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::Long),      "LongTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::Float),     "FloatTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::Double),    "DoubleTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::ByteArray), "ByteArrayTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::String),    "StringTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::List),      "ListTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::Compound),  "CompoundTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::IntArray),  "IntArrayTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::LongArray), "LongArrayTag");
    EXPECT_EQ(anvil::getTagName(anvil::TagType::Unknown),   "UnknownTag");
}