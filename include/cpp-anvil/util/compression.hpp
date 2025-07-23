#ifndef CPP_ANVIL_IO_COMPRESSION_HPP
#define CPP_ANVIL_IO_COMPRESSION_HPP

#include <fstream>
#include <vector>

namespace anvil {

//! @brief The supported compression types.
enum class CompressionType : char
{
    Gzip = 1,
    Zlib = 2,
    Uncompressed = 3,
};

enum CompressionLevel : char
{
    DefaultCompression = -1,
    NoCompression = 0,
    BestSpeed = 1,
    BestCompression = 9,
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

// -------------------------------------------------------------------------------------------------
//      inflate / uncompress
// -------------------------------------------------------------------------------------------------

//! @brief Uncompresses gzip data stream into byte vector.
//! 
//! @param strm The stream to read compressed data bytes from.
//! @param data The target container to write the uncompressed data to. The container will be 
//!             cleared and resized to fit to the uncompressed data.
//! 
//! @return `true` if uncompressing succeeded, `false` otherwise.
bool inflate_gzip(std::ifstream &strm, std::vector<unsigned char> &data);

//! @brief Uncompresses gzip data sequence into byte vector. 
//! 
//! @param in  input vector of gzip compressed data.
//! @param out output vector of uncompressed input data.
//! 
//! @return `true` if uncompressing succeeded, `false` otherwise.
bool inflate_gzip(const std::vector<unsigned char> &in, std::vector<unsigned char> &out);

//! @brief Uncompresses zlib data stream into byte vector.
//! 
//! @param strm The stream to read compressed data bytes from.
//! @param data The target container to write the uncompressed data to. The container will be 
//!             cleared and resized to fit to the uncompressed data.
//! 
//! @return `true` if uncompressing succeeded, `false` otherwise.
bool inflate_zlib(std::ifstream &strm, std::vector<unsigned char> &data);

//! @brief Uncompresses zlib data sequence into byte vector. 
//! 
//! @param in  input vector of zlib compressed data.
//! @param out output vector of uncompressed input data.
//! 
//! @return `true` if uncompressing succeeded, `false` otherwise.
bool inflate_zlib(const std::vector<unsigned char> &in, std::vector<unsigned char> &out);

// -------------------------------------------------------------------------------------------------
//      deflate / compress
// -------------------------------------------------------------------------------------------------

//! @brief Compresses data sequence with gzip compression algorithm.
//! 
//! @param strm             The stream where the compressed data is written to.
//! @param data             The input data sequence to be compressed.
//! @param compressionLevel The compression level.
//! 
//! @return `true` if compression succeeded, `false` otherwise.
bool deflate_gzip(std::ofstream &strm,
                  std::vector<unsigned char> &data,
                  const int compressionLevel = DefaultCompression);

//! @brief Compresses data sequence with gzip compression algorithm.
//! 
//! @param in               The input data sequence to be compressed.
//! @param out              The output data sequence of compressed data.
//! @param compressionLevel The compression level.
//! 
//! @return `true` if compression succeeded, `false` otherwise.
bool deflate_gzip(const std::vector<unsigned char> &in,
                  std::vector<unsigned char> &out,
                  const int compressionLevel = DefaultCompression);

//! @brief Compresses data sequence with zlib compression algorithm.
//! 
//! @param strm             The stream where the compressed data is written to.
//! @param data             The input data sequence to be compressed.
//! @param compressionLevel The compression level.
//! 
//! @return `true` if compression succeeded, `false` otherwise.
bool deflate_zlib(std::ofstream &strm,
                  std::vector<unsigned char> &data,
                  const int compressionLevel = DefaultCompression);

//! @brief Compresses data sequence with zlib compression algorithm.
//! 
//! @param in               The input data sequence to be compressed.
//! @param out              The output data sequence of compressed data.
//! @param compressionLevel The compression level.
//! 
//! @return `true` if compression succeeded, `false` otherwise.
bool deflate_zlib(const std::vector<unsigned char> &in,
                  std::vector<unsigned char> &out,
                  const int compressionLevel = DefaultCompression);

} // namespace anvil

#endif // CPP_ANVIL_IO_COMPRESSION_HPP
