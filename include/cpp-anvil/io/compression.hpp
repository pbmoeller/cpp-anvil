#ifndef CPP_ANVIL_IO_COMPRESSION_HPP
#define CPP_ANVIL_IO_COMPRESSION_HPP

// STL
#include <fstream>
#include <vector>

namespace nbt {
namespace io {

enum class CompressionType
{
    Gzip = 1,
    Zlib = 2,
    Uncompressed = 3,
};

constexpr bool isGzipCompressed(const std::vector<unsigned char> &data) {
    return (data.size() >= 2) 
        && (data[0] == 0x1F && data[1] == 0x8B);
}

constexpr bool isZlibCompressed(const std::vector<unsigned char> &data) {
    return (data.size() >= 2) 
        && (data[0] == 0x78 
            && (data[1] == 0x8B || data[1] == 0x5E || data[1] == 0x9C || data[1] == 0xDA));
}
constexpr bool isUncompressed(const std::vector<unsigned char> &data) {
    return !isGzipCompressed(data) && !isZlibCompressed(data);
}

CompressionType testCompression(const std::vector<unsigned char> &data);

bool uncompress(std::ifstream &strm, std::vector<unsigned char> &data);

bool inflate_gzip(std::ifstream &strm, std::vector<unsigned char> &data);
bool inflate_zlib(std::ifstream &strm, std::vector<unsigned char> &data);

bool deflate_gzip(std::ifstream &strm, std::vector<unsigned char> &data);
bool deflate_zlib(std::ifstream &strm, std::vector<unsigned char> &data);

} // namespace io
} // namespace nbt

#endif // CPP_ANVIL_IO_COMPRESSION_HPP