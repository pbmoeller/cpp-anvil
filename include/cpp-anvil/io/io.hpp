#ifndef CPP_ANVIL_IO_IO_HPP
#define CPP_ANVIL_IO_IO_HPP

// cpp-anvil
#include <cpp-anvil/nbt.hpp>
#include <cpp-anvil/io/compression.hpp>

// STL
#include <memory>

namespace nbt {
namespace io {

std::unique_ptr<CompoundTag> loadFile(const std::string &filename);
std::unique_ptr<CompoundTag> loadFile(const std::string &filename,
                                      CompressionType &compressionType);

std::unique_ptr<CompoundTag> readData(std::vector<unsigned char> &data);

std::string printTag(const BasicTag *compoundTag, int indent = 2, bool printArrayContent = false);

} // namespace io
} // namespace nbt

#endif // CPP_ANVIL_IO_IO_HPP
