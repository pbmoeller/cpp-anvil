#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cpp-anvil/util/compression.hpp>

#include "test_data.hpp"

TEST(compression, deflate_inflate_zlib)
{
    std::vector<unsigned char> input(&bigtestUncompressedData[0], &bigtestUncompressedData[1544]);

    std::vector<unsigned char> intermediate;
    std::vector<unsigned char> output;

    EXPECT_TRUE(anvil::deflate_zlib(input, intermediate, -1));
    EXPECT_TRUE(anvil::inflate_zlib(intermediate, output));

    EXPECT_TRUE(anvil::isZlibCompressed(intermediate));

    EXPECT_THAT(std::vector<unsigned char>(output.begin(), output.begin() + output.size()),
                ::testing::ElementsAreArray(&bigtestUncompressedData[0],
                                            &bigtestUncompressedData[0] + 1544));
}

TEST(compression, deflate_inflate_gzip)
{
    std::vector<unsigned char> input(&bigtestUncompressedData[0], &bigtestUncompressedData[1544]);

    std::vector<unsigned char> intermediate;
    std::vector<unsigned char> output;

    EXPECT_TRUE(anvil::deflate_gzip(input, intermediate, -1));
    EXPECT_TRUE(anvil::inflate_gzip(intermediate, output));

    EXPECT_TRUE(anvil::isGzipCompressed(intermediate));

    EXPECT_THAT(std::vector<unsigned char>(output.begin(), output.begin() + output.size()),
                ::testing::ElementsAreArray(&bigtestUncompressedData[0],
                                            &bigtestUncompressedData[0] + 1544));
}
