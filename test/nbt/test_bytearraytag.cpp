#include <gtest/gtest.h>

#include <cpp-anvil/nbt.hpp>

TEST(ByteArrayTag, Constructor)
{
    std::vector<anvil::ByteType> vec;

    anvil::ByteArrayTag arrayTag;
    EXPECT_EQ(arrayTag.type(), anvil::TagType::ByteArray);
    EXPECT_EQ(arrayTag.name(), "");
    EXPECT_EQ(arrayTag.value(), vec);
}

TEST(ByteArrayTag, Constructor_Name)
{
    std::vector<anvil::ByteType> vec;

    const std::string name = "Some Name";
    anvil::ByteArrayTag arrayTag(name);
    EXPECT_EQ(arrayTag.type(), anvil::TagType::ByteArray);
    EXPECT_EQ(arrayTag.name(), name);
    EXPECT_EQ(arrayTag.value(), vec);
}

TEST(ByteArrayTag, Constructor_Value)
{
    const std::vector<anvil::ByteType> vec{0x45};

    anvil::ByteArrayTag arrayTag(vec);
    EXPECT_EQ(arrayTag.type(), anvil::TagType::ByteArray);
    EXPECT_EQ(arrayTag.name(), "");
    EXPECT_EQ(arrayTag.value(), vec);
}

TEST(ByteArrayTag, Constructor_Name_Value)
{
    const std::string name = "Some Name";
    const std::vector<anvil::ByteType> vec{0x35};

    anvil::ByteArrayTag arrayTag(name, vec);
    EXPECT_EQ(arrayTag.type(), anvil::TagType::ByteArray);
    EXPECT_EQ(arrayTag.name(), name);
    EXPECT_EQ(arrayTag.value(), vec);
}

TEST(ByteArrayTag, Constructor_Copy)
{
    const std::string name = "Copy Test";
    const std::vector<anvil::ByteType> vec{0x35};

    anvil::ByteArrayTag arrayTagA(name, vec);
    EXPECT_EQ(arrayTagA.type(), anvil::TagType::ByteArray);
    EXPECT_EQ(arrayTagA.name(), name);
    EXPECT_EQ(arrayTagA.value(), vec);

    anvil::ByteArrayTag arrayTagB(arrayTagA);
    EXPECT_EQ(arrayTagB.type(), anvil::TagType::ByteArray);
    EXPECT_EQ(arrayTagB.name(), name);
    EXPECT_EQ(arrayTagB.value(), vec);

    EXPECT_EQ(arrayTagA, arrayTagB);
}

TEST(ByteArrayTag, Constructor_Move)
{
    const std::string name = "Move Test";
    const std::vector<anvil::ByteType> vec{0x64};

    anvil::ByteArrayTag arrayTagA(name, vec);
    EXPECT_EQ(arrayTagA.type(), anvil::TagType::ByteArray);
    EXPECT_EQ(arrayTagA.name(), name);
    EXPECT_EQ(arrayTagA.value(), vec);

    anvil::ByteArrayTag arrayTagB(std::move(arrayTagA));
    EXPECT_EQ(arrayTagB.type(), anvil::TagType::ByteArray);
    EXPECT_EQ(arrayTagB.name(), name);
    EXPECT_EQ(arrayTagB.value(), vec);

    EXPECT_NE(arrayTagA, arrayTagB);
}

TEST(ByteArrayTag, push_back)
{
    std::vector<anvil::ByteType> vec;
    std::vector<anvil::ByteType> vec2(2, 0xAB);

    anvil::ByteArrayTag arrayTag;
    EXPECT_EQ(arrayTag.type(), anvil::TagType::ByteArray);
    EXPECT_EQ(arrayTag.name(), "");
    EXPECT_EQ(arrayTag.value(), vec);
    EXPECT_TRUE(arrayTag.empty());
    EXPECT_EQ(arrayTag.size(), 0);

    EXPECT_TRUE(arrayTag.push_back(0xAB));
    EXPECT_NE(arrayTag.value(), vec);
    EXPECT_NE(arrayTag.value(), vec2);
    EXPECT_FALSE(arrayTag.empty());
    EXPECT_EQ(arrayTag.size(), 1);

    EXPECT_TRUE(arrayTag.push_back(0xAB));
    EXPECT_NE(arrayTag.value(), vec);
    EXPECT_EQ(arrayTag.value(), vec2);
    EXPECT_FALSE(arrayTag.empty());
    EXPECT_EQ(arrayTag.size(), 2);
}

TEST(ByteArrayTag, at)
{
    const std::string name{"Test"};
    const std::vector<anvil::ByteType> vec{10, 20, 30, 40};
    anvil::ByteArrayTag arrayTag(name, vec);
    
    EXPECT_FALSE(arrayTag.empty());
    EXPECT_EQ(arrayTag.size(), 4);

    EXPECT_EQ(arrayTag.at(0), 10);
    EXPECT_EQ(arrayTag.at(1), 20);
    EXPECT_EQ(arrayTag.at(2), 30);
    EXPECT_EQ(arrayTag.at(3), 40);
}

TEST(ByteArrayTag, Operator_Subscript)
{
    const std::string name{"Test"};
    const std::vector<anvil::ByteType> vec{10, 20, 30, 40};
    anvil::ByteArrayTag arrayTag(name, vec);

    EXPECT_FALSE(arrayTag.empty());
    EXPECT_EQ(arrayTag.size(), 4);

    EXPECT_EQ(arrayTag[0], 10);
    EXPECT_EQ(arrayTag[1], 20);
    EXPECT_EQ(arrayTag[2], 30);
    EXPECT_EQ(arrayTag[3], 40);
}

TEST(ByteArrayTag, Front_Back)
{
    const std::string name{"Test"};
    const std::vector<anvil::ByteType> vec{10, 20, 30, 40};
    anvil::ByteArrayTag arrayTag(name, vec);

    EXPECT_FALSE(arrayTag.empty());
    EXPECT_EQ(arrayTag.size(), 4);

    EXPECT_EQ(arrayTag.front(), 10);
    EXPECT_EQ(arrayTag.back(), 40);

    EXPECT_TRUE(arrayTag.push_back(0x34));
    EXPECT_EQ(arrayTag.back(), 0x34);
}

TEST(ByteArrayTag, clear)
{
    const std::string name{"Test"};
    const std::vector<anvil::ByteType> vec{10, 20, 30, 40};
    anvil::ByteArrayTag arrayTag(name, vec);

    EXPECT_FALSE(arrayTag.empty());
    EXPECT_EQ(arrayTag.size(), 4);

    arrayTag.clear();
    EXPECT_TRUE(arrayTag.empty());
    EXPECT_EQ(arrayTag.size(), 0);
}