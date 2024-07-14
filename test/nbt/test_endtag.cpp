#include <gtest/gtest.h>

#include <cpp-anvil/nbt.hpp>

TEST(EndTag, Constructor)
{
    nbt::EndTag endTag;
    EXPECT_EQ(endTag.type(), nbt::TagType::End);
}

TEST(EndTag, Equality)
{
    nbt::EndTag endTagA;
    nbt::EndTag endTagB;
    EXPECT_TRUE(endTagA == endTagA);    // Same object
    EXPECT_TRUE(endTagA == endTagB);    // Other object
}

TEST(EndTag, InEquality)
{
    nbt::EndTag endTagA;
    nbt::EndTag endTagB;
    EXPECT_FALSE(endTagA != endTagA);    // Same object
    EXPECT_FALSE(endTagA != endTagB);    // Other object
}

TEST(EndTag, tag_cast)
{
    nbt::BasicTag *endTag = new nbt::EndTag();

    nbt::EndTag *otherTag = nbt::tag_cast<nbt::EndTag*>(endTag);
    EXPECT_EQ(otherTag, endTag);

    delete endTag;
}

TEST(EndTag, clone)
{
    auto endTag = nbt::EndTag();
    auto endTag2 = endTag.clone();

    EXPECT_EQ(endTag, *endTag2);
}