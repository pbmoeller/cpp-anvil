#ifndef CPP_ANVIL_IO_COMPRESSION_HPP
#define CPP_ANVIL_IO_COMPRESSION_HPP

// STL
#include <fstream>
#include <vector>

namespace anvil {

//! @brief The supported compression types.
enum class CompressionType
{
    Gzip = 1,
    Zlib = 2,
    Uncompressed = 3,
};

//! @brief Checks if sequence of bytes begins with Gzip header.
//! 
//! @param data The data to be checked.
//! 
//! @return `true` if the first 2 bytes in the sequence indicate a Gzip header, `false` otherwise.
constexpr bool isGzipCompressed(const std::vector<unsigned char> &data) {
    return (data.size() >= 2) 
        && (data[0] == 0x1F && data[1] == 0x8B);
}

//! @brief Checks if sequence of bytes begins with Zlib header.
//! 
//! @param data The data to be checked.
//! 
//! @return `true` if the first 2 bytes in the sequence indicate a Zlib header, `false` otherwise.
constexpr bool isZlibCompressed(const std::vector<unsigned char> &data) {
    return (data.size() >= 2) 
        && (data[0] == 0x78 
            && (data[1] == 0x8B || data[1] == 0x5E || data[1] == 0x9C || data[1] == 0xDA));
}

//! @brief Checks if sequence of bytes begins with neither Zlib or Gzip header.
//! 
//! @param data The data to be checked.
//! 
//! @return `true` if the first 2 bytes do not indicate Gzip or Zlib header, `false` otherwise.
constexpr bool isUncompressed(const std::vector<unsigned char> &data) {
    return !isGzipCompressed(data) && !isZlibCompressed(data);
}

//! @brief Tests type of compression of the data sequence by looking for Gzip or Zlib header.
//! 
//! @param data The data to be checked.
//! 
//! @return CompressionType of data sequence.
CompressionType testCompression(const std::vector<unsigned char> &data);

//! @brief Uncompresses gzip data stream into byte vector.
//! 
//! @param strm The stream to read compressed data bytes from.
//! @param data The target container to write the uncompressed data to. The container will be 
//!             cleared and resized to fit to the uncompressed data.
//! 
//! @return `true` if uncompressing succeeded, `false` otherwise.
bool inflate_gzip(std::ifstream &strm, std::vector<unsigned char> &data);

//! @brief Uncompresses zlib data stream into byte vector.
//! 
//! @param strm The stream to read compressed data bytes from.
//! @param data The target container to write the uncompressed data to. The container will be 
//!             cleared and resized to fit to the uncompressed data.
//! 
//! @return `true` if uncompressing succeeded, `false` otherwise.
bool inflate_zlib(std::ifstream &strm, std::vector<unsigned char> &data);

bool deflate_gzip(std::ifstream &strm, std::vector<unsigned char> &data);
bool deflate_zlib(std::ifstream &strm, std::vector<unsigned char> &data);

} // namespace anvil

#endif // CPP_ANVIL_IO_COMPRESSION_HPP
