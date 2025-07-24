#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cpp-anvil/nbt/io.hpp>

#include "test_data.hpp"

TEST(io, load_file_gzip)
{
    const std::string testFolderNbt = "../../../test/data/";

    anvil::CompressionType type;
    auto ctag = anvil::loadFromFile(testFolderNbt + "bigtest.nbt", type);
    ASSERT_TRUE(ctag != nullptr);
    EXPECT_EQ(type, anvil::CompressionType::Gzip);

    std::vector<unsigned char> data = anvil::writeData(ctag.get());

    EXPECT_THAT(std::vector<unsigned char>(data.begin(), data.begin() + data.size()),
                ::testing::ElementsAreArray(&bigtestUncompressedData[0],
                                            &bigtestUncompressedData[0] + 1544));
}

TEST(io, save_to_file_gzip)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}
