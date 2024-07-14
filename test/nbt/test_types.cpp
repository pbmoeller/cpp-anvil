#include <gtest/gtest.h>

#include <cpp-anvil/nbt.hpp>

TEST(TagType, Types)
{
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::End),        0);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::Byte),       1);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::Short),      2);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::Int),        3);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::Long),       4);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::Float),      5);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::Double),     6);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::ByteArray),  7);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::String),     8);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::List),       9);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::Compound),   10);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::IntArray),   11);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::LongArray),  12);
    EXPECT_EQ(static_cast<unsigned char>(nbt::TagType::Unknown),    255);
}

TEST(TagType, isPrimitiveTag)
{
    EXPECT_FALSE(nbt::isPrimitiveTag(nbt::TagType::End));
    EXPECT_TRUE(nbt::isPrimitiveTag(nbt::TagType::Byte));
    EXPECT_TRUE(nbt::isPrimitiveTag(nbt::TagType::Short));
    EXPECT_TRUE(nbt::isPrimitiveTag(nbt::TagType::Int));
    EXPECT_TRUE(nbt::isPrimitiveTag(nbt::TagType::Long));
    EXPECT_TRUE(nbt::isPrimitiveTag(nbt::TagType::Float));
    EXPECT_TRUE(nbt::isPrimitiveTag(nbt::TagType::Double));
    EXPECT_FALSE(nbt::isPrimitiveTag(nbt::TagType::ByteArray));
    EXPECT_TRUE(nbt::isPrimitiveTag(nbt::TagType::String));
    EXPECT_FALSE(nbt::isPrimitiveTag(nbt::TagType::List));
    EXPECT_FALSE(nbt::isPrimitiveTag(nbt::TagType::Compound));
    EXPECT_FALSE(nbt::isPrimitiveTag(nbt::TagType::IntArray));
    EXPECT_FALSE(nbt::isPrimitiveTag(nbt::TagType::LongArray));
    EXPECT_FALSE(nbt::isPrimitiveTag(nbt::TagType::Unknown));
}

TEST(TagType, isArrayTag)
{
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::End));
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::Byte));
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::Short));
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::Int));
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::Long));
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::Float));
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::Double));
    EXPECT_TRUE(nbt::isArrayTag(nbt::TagType::ByteArray));
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::String));
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::List));
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::Compound));
    EXPECT_TRUE(nbt::isArrayTag(nbt::TagType::IntArray));
    EXPECT_TRUE(nbt::isArrayTag(nbt::TagType::LongArray));
    EXPECT_FALSE(nbt::isArrayTag(nbt::TagType::Unknown));
}

TEST(TagType, isContainerTag)
{
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::End));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::Byte));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::Short));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::Int));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::Long));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::Float));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::Double));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::ByteArray));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::String));
    EXPECT_TRUE(nbt::isContainerTag(nbt::TagType::List));
    EXPECT_TRUE(nbt::isContainerTag(nbt::TagType::Compound));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::IntArray));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::LongArray));
    EXPECT_FALSE(nbt::isContainerTag(nbt::TagType::Unknown));
}

TEST(TagType, isCollectionTag)
{
    EXPECT_FALSE(nbt::isCollectionTag(nbt::TagType::End));
    EXPECT_FALSE(nbt::isCollectionTag(nbt::TagType::Byte));
    EXPECT_FALSE(nbt::isCollectionTag(nbt::TagType::Short));
    EXPECT_FALSE(nbt::isCollectionTag(nbt::TagType::Int));
    EXPECT_FALSE(nbt::isCollectionTag(nbt::TagType::Long));
    EXPECT_FALSE(nbt::isCollectionTag(nbt::TagType::Float));
    EXPECT_FALSE(nbt::isCollectionTag(nbt::TagType::Double));
    EXPECT_TRUE(nbt::isCollectionTag(nbt::TagType::ByteArray));
    EXPECT_FALSE(nbt::isCollectionTag(nbt::TagType::String));
    EXPECT_TRUE(nbt::isCollectionTag(nbt::TagType::List));
    EXPECT_TRUE(nbt::isCollectionTag(nbt::TagType::Compound));
    EXPECT_TRUE(nbt::isCollectionTag(nbt::TagType::IntArray));
    EXPECT_TRUE(nbt::isCollectionTag(nbt::TagType::LongArray));
    EXPECT_FALSE(nbt::isCollectionTag(nbt::TagType::Unknown));
}

TEST(TagType, isValueTag)
{
    EXPECT_FALSE(nbt::isValueTag(nbt::TagType::End));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::Byte));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::Short));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::Int));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::Long));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::Float));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::Double));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::ByteArray));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::String));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::List));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::Compound));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::IntArray));
    EXPECT_TRUE(nbt::isValueTag(nbt::TagType::LongArray));
    EXPECT_FALSE(nbt::isValueTag(nbt::TagType::Unknown));
}

TEST(TagType, isValidTag)
{
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::End));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::Byte));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::Short));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::Int));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::Long));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::Float));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::Double));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::ByteArray));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::String));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::List));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::Compound));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::IntArray));
    EXPECT_TRUE(nbt::isValidTag(nbt::TagType::LongArray));
    EXPECT_FALSE(nbt::isValidTag(nbt::TagType::Unknown));
}

TEST(TagType, getTagTypeName)
{
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::End),       "End");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::Byte),      "Byte");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::Short),     "Short");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::Int),       "Int");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::Long),      "Long");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::Float),     "Float");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::Double),    "Double");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::ByteArray), "ByteArray");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::String),    "String");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::List),      "List");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::Compound),  "Compound");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::IntArray),  "IntArray");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::LongArray), "LongArray");
    EXPECT_EQ(nbt::getTagTypeName(nbt::TagType::Unknown),   "Unknown");
}

TEST(TagType, getTagName)
{
    EXPECT_EQ(nbt::getTagName(nbt::TagType::End),       "EndTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::Byte),      "ByteTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::Short),     "ShortTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::Int),       "IntTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::Long),      "LongTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::Float),     "FloatTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::Double),    "DoubleTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::ByteArray), "ByteArrayTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::String),    "StringTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::List),      "ListTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::Compound),  "CompoundTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::IntArray),  "IntArrayTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::LongArray), "LongArrayTag");
    EXPECT_EQ(nbt::getTagName(nbt::TagType::Unknown),   "UnknownTag");
}