#ifndef CPP_ANVIL_IO_IO_HPP
#define CPP_ANVIL_IO_IO_HPP

// cpp-anvil
#include <cpp-anvil/nbt.hpp>
#include <cpp-anvil/util/compression.hpp>

// STL
#include <memory>

namespace anvil {

//! @brief Checks if the file contains NBT data.
//! 
//! The data is not completely parsed. The functions checks if the file is compressed. If the file
//! is compressed then the file will be uncompressed and the first byte of the uncompressed
//! data ist checked. If this indicates a CompounTag the functions returns true.
//! 
//! If you plan to parse the file anyway, then just load the file and check if this succeeded. This
//! will be more fficient than calling this function and the loading afterwards.
//! 
//! @param filename The filename to check.
//! 
//! @return `true` is file contaisn NBT data, `false` otherwise.
bool isNbtFile(const std::string &filename);

//! @brief Tries to load a NBT file.
//! 
//! @param filename File with NBT content. May be compressed with either `Zlib` or `Gzip` 
//!                 compression.
//! 
//! @return A CompoundTag containing the NBT data.
std::unique_ptr<CompoundTag> loadFromFile(const std::string &filename);
 
//! @brief Tries to load a NBT file and returns \p compressionType of the raw data.
//! 
//! @param filename         File with NBT content. May be compressed with either `Zlib` or `Gzip`
//!                         compression.
//! @param compressionType  On successful read the parameter contains the compression type of the
//!                         original data.
//! 
//! @return A CompoundTag containing the NBT data.
std::unique_ptr<CompoundTag> loadFromFile(const std::string &filename,
                                          CompressionType &compressionType);

//! @brief Writes a byte sequence of data to file.
//! 
//! @param filename Filename to writte data to.
//! @param data     Data to be saved.
//! 
//! @return `true` on success, `false` otherwise.
bool saveToFile(const std::string &filename, std::vector<unsigned char> &data);

//! @brief Writes a byte sequence of data to file.
//! 
//! @param filename         Filename to writte data to.
//! @param data             Data to be saved.
//! @param compressionType  The compression type if the data should be compressed.
//! 
//! @return `true` on success, `false` otherwise.
bool saveToFile(const std::string &filename, std::vector<unsigned char> &data,
                CompressionType compressionType);

//! @brief Writes a byte sequence of data to file.
//! 
//! @param filename         Filename to writte data to.
//! @param data             Data to be saved.
//! @param compressionType  The compression type if the data should be compressed.
//! @param compressionLevel The level of compression.
//! 
//! @return `true` on success, `false` otherwise.
bool saveToFile(const std::string &filename, std::vector<unsigned char> &data,
                CompressionType compressionType, int compressionLevel);

//! @brief Serializes the CompoundTag and saves the data to file.
//! 
//! @param filename     Filename where the serialized tag is written to.
//! @param compoundTag  The CompoundTag to be serialized.
//! 
//! @return `true` on success, `false` otherwise.
bool saveToFile(const std::string &filename, const CompoundTag *compoundTag);

//! @brief Serializes the CompoundTag and saves the data to file.
//! 
//! @param filename         Filename where the serialized tag is written to.
//! @param compoundTag      The CompoundTag to be serialized.
//! @param compressionType  The compression type if the data should be compressed.
//! 
//! @return `true` on success, `false` otherwise.
bool saveToFile(const std::string &filename, const CompoundTag *compoundTag,
                CompressionType compressionType);

//! @brief Serializes the CompoundTag and saves the data to file.
//! 
//! @param filename         Filename where the serialized tag is written to.
//! @param compoundTag      The CompoundTag to be serialized.
//! @param compressionType  The compression type if the data should be compressed.
//! @param compressionLevel The level of compression.
//! 
//! @return `true` on success, `false` otherwise.
bool saveToFile(const std::string &filename, const CompoundTag *compoundTag,
                CompressionType compressionType, int compressionLevel);

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

} // namespace anvil

#endif // CPP_ANVIL_IO_IO_HPP
