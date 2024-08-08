#ifndef CPP_ANVIL_IO_IO_HPP
#define CPP_ANVIL_IO_IO_HPP

// cpp-anvil
#include <cpp-anvil/nbt.hpp>
#include <cpp-anvil/io/compression.hpp>

// STL
#include <memory>

namespace nbt {
namespace io {

//! @brief Tries to load a NBT file.
//! 
//! @param filename File with NBT content. May be compressed with either `Zlib` or `Gzip` 
//!                 compression.
//! 
//! @return A CompoundTag containing the NBT data.
std::unique_ptr<CompoundTag> loadFile(const std::string &filename);
 
//! @brief Tries to load a NBT file and returns \p compressionType of the raw data.
//! 
//! @param filename         File with NBT content. May be compressed with either `Zlib` or `Gzip`
//!                         compression.
//! @param compressionType  On successful read the parameter contains the compression type of the
//!                         original data.
//! 
//! @return A CompoundTag containing the NBT data.
std::unique_ptr<CompoundTag> loadFile(const std::string &filename,
                                      CompressionType &compressionType);

//! @brief Deserializes a sequence of bytes into a NBT CompoundTag.
//! 
//! The first tag in the sequence must be a CompoundTag.
//! 
//! @param data  Sequence of bytes to be deserialized.
//! 
//! @return CompoudTag with all contents.
std::unique_ptr<CompoundTag> readData(std::vector<unsigned char> &data);

//! @brief Serializes a NBT tag into a sequence of bytes.
//! 
//! @param tag  The tag to be serialized.
//! 
//! @return Serialized sequence of bytes.
std::vector<unsigned char> writeData(const BasicTag *tag);

//! @brief Prints the \p tag and its contents.
//! 
//! @param tag                  The to be printed.
//! @param indent               Indentation for inner tags.
//! @param printArrayContent    If the contents of arrays should be printed.
//! 
//! @return The printed NBT tags as string.
std::string printTag(const BasicTag *tag, int indent = 2, bool printArrayContent = false);

} // namespace io
} // namespace nbt

#endif // CPP_ANVIL_IO_IO_HPP
