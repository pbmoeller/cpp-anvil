// cpp-anvil
#include <cpp-anvil/anvil/region.hpp>
#include <cpp-anvil/util/compression.hpp>

#include "util/byte_swap.hpp"
#include "anvil/region_header.hpp"

// STL
#include <regex>
#include <fstream>
#include <filesystem>

namespace anvil {

Region::Region()
{
    m_loadedChunks.fill(false);
    m_chunkCompression.fill(CompressionType::Uncompressed);
}

void Region::loadFromFile(const std::string &filename)
{
    loadPartiallyFromFile(filename);

    loadAllChunks();
}

void Region::loadPartiallyFromFile(const std::string &filename)
{
    // Check if region filename is valid and extract region coordinates
    int x = 0;
    int z = 0;
    if(!validateAndParseRegionFilename(filename, x, z)) {
        throw std::runtime_error("Invalid region filename.");
    }

    // Open filestream for reading
    std::ifstream stream(filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error("Failed to open region file.");
    }

    // Read region file header data
    if(!readRegionHeader(stream)) {
        throw std::runtime_error("Failed to read region header.");
    }

    // Store infos of the current region file
    m_x = x;
    m_z = z;
    m_filename = filename;
}

void Region::loadChunkAt(size_t index)
{
    if(index >= Chunks) {
        throw std::out_of_range("Index is out of range.");
    }

    // If the chunk is already loaded or the chunk is marked as empty, we are done here
    if(m_loadedChunks[index] || m_regionHeader->empty(index)) {
        return;
    }

    // Open filestream
    std::ifstream stream(m_filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error("Failed to open region file.");
    }

    readChunkData(stream, index);
}

void Region::loadAllChunks()
{
    // Open filestream
    std::ifstream stream(m_filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error("Failed to open region file.");
    }

    // Iterate through all chunks and load if not already loaded or empty.
    for(size_t chunkIndex = 0; chunkIndex < Chunks; ++chunkIndex) {
        if(m_loadedChunks[chunkIndex] || m_regionHeader->empty(chunkIndex)) {
            continue;
        }

        readChunkData(stream, chunkIndex);
    }
}

Chunk& Region::chunkAt(size_t index)
{
    if(index >= Chunks) {
        throw std::out_of_range("Index is out of range.");
    }

    return m_chunks[index];
}

const Chunk& Region::chunkAt(size_t index) const
{
    if(index >= Chunks) {
        throw std::out_of_range("Index is out of range.");
    }

    return m_chunks[index];
}

void Region::readChunkData(std::ifstream &filestream, const size_t index)
{
    // Seek to beginning of chunk data in the filestream
    size_t offset = m_regionHeader->byteOffset(index);
    filestream.seekg(offset, std::ios::beg);

    // Get size of binary data and compression type
    uint32_t dataSize = 0;
    filestream.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32_t));
    dataSize = detail::swapEndian(dataSize);
    CompressionType compressionType = CompressionType::Uncompressed;
    filestream.read(reinterpret_cast<char*>(&compressionType), sizeof(char));

    // Read the chunk data
    std::vector<unsigned char> compressedChunkData(dataSize - 1, 0);
    filestream.read(reinterpret_cast<char*>(&compressedChunkData[0]), dataSize - 1);

    std::vector<unsigned char> chunkData;
    switch(compressionType) {
        case CompressionType::Gzip:
            if(!inflate_gzip(compressedChunkData, chunkData)) {
                throw std::runtime_error("Failed to uncompress chunk data (gzip).");
            }
            break;
        case CompressionType::Zlib:
            if(!inflate_zlib(compressedChunkData, chunkData)) {
                throw std::runtime_error("Failed to uncompress chunk data (zlib).");
            }
            break;
        case CompressionType::Uncompressed:
            break;
        default:
            throw std::runtime_error("Unknown compression type.");
    }

    chunkAt(index).setRootTag(readData(chunkData));
    m_chunkCompression[index] = compressionType;
    m_loadedChunks[index] = true;
}

bool Region::readRegionHeader(std::ifstream &filestream)
{
    m_regionHeader = std::make_unique<RegionHeader>();
    return m_regionHeader->loadFromStream(filestream);
}

bool Region::validateRegionFilename(const std::string &filename)
{
    int x = 0;
    int z = 0;
    return validateAndParseRegionFilename(filename, x, z);
}

bool Region::validateAndParseRegionFilename(const std::string &filename, int &x, int &z)
{
    // Pattern definition of Minecraft region file.
    const std::regex RegionFilePattern 
        = std::regex("r\\.(0|[-]?[1-9][0-9]*)\\.(0|[-]?[1-9][0-9]*)\\.mca");

    // Convert filename so that preferred directory separators are used.
    std::filesystem::path filepath{filename};
    std::string convertedFilename = filepath.make_preferred().string();

    // Extract the filename from the whole path
    size_t offset = convertedFilename.find_last_of(std::filesystem::path::preferred_separator) + 1;
    std::string name = convertedFilename.substr(offset + 1);

    // Search for region file pattern : 'r.X.Z.mca'
    std::cmatch ref;
    if(!std::regex_match(name.c_str(), ref, RegionFilePattern)) {
        return false;
    }

    // If the pattern was found set X and Z values and return success
    x = std::atoi(ref[1].str().c_str());
    z = std::atoi(ref[2].str().c_str());
    return true;
}

} // namespace anvil
