#include <gtest/gtest.h>

#include <cpp-anvil/nbt.hpp>

TEST(EndTag, Constructor)
{
    anvil::EndTag endTag;
    EXPECT_EQ(endTag.type(), anvil::TagType::End);
}

TEST(EndTag, Equality)
{
    anvil::EndTag endTagA;
    anvil::EndTag endTagB;
    EXPECT_TRUE(endTagA == endTagA); // Same object
    EXPECT_TRUE(endTagA == endTagB); // Other object
}

TEST(EndTag, InEquality)
{
    anvil::EndTag endTagA;
    anvil::EndTag endTagB;
    EXPECT_FALSE(endTagA != endTagA); // Same object
    EXPECT_FALSE(endTagA != endTagB); // Other object
}

TEST(EndTag, tag_cast)
{
    anvil::BasicTag* endTag = new anvil::EndTag();

    anvil::EndTag* otherTag = anvil::tag_cast<anvil::EndTag*>(endTag);
    EXPECT_EQ(otherTag, endTag);

    delete endTag;
}

TEST(EndTag, clone)
{
    auto endTag  = anvil::EndTag();
    auto endTag2 = endTag.clone();

    EXPECT_EQ(endTag, *endTag2);
}
