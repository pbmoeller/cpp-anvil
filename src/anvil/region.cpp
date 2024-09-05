// cpp-anvil
#include <cpp-anvil/anvil/region.hpp>
#include <cpp-anvil/nbt/io.hpp>
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

Region::~Region() = default;

void Region::loadFromFile(const std::string &filename)
{
    loadPartiallyFromFile(filename);

    loadAllChunks();
}

void Region::loadPartiallyFromFile(const std::string &filename)
{
    // Check if region filename is valid and extract region coordinates
    int32_t x = 0;
    int32_t z = 0;
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
    if(isChunkLoaded(index) || !isChunkLoadable(index)) {
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
        if(!isChunkLoaded(chunkIndex) && isChunkLoadable(chunkIndex)) {
            readChunkData(stream, chunkIndex);
        }
    }
}

bool Region::isChunkLoaded(size_t index) const
{
    return m_loadedChunks[index];
}

bool Region::isChunkLoadable(size_t index) const
{
    return m_regionHeader && !m_regionHeader->empty(index);
}

bool Region::saveToFile()
{
    return saveToFile(m_filename);
}

bool Region::saveToFile(const std::string &filename)
{
    std::vector<unsigned char> regionData(RegionHeader::HeaderSize, 0);
    size_t storageDataOffset = RegionHeader::HeaderSize;
    RegionHeader regionHeader;

    for(size_t index = 0; index < Chunks; ++index) {
        if(m_chunks[index].empty()) {
            regionHeader.setChunkData(index, 0, 0, 0);
        } else {
            CompressionType compression = m_chunkCompression[index];
            CompoundTag *rootTag = m_chunks[index].rootTag();

            // Compress the serialized chunk data.
            std::vector<unsigned char> serializedData = writeData(rootTag);
            std::vector<unsigned char> chunkData;
            if(compression == CompressionType::Zlib) {
                // This is the usual case
                if(!deflate_zlib(serializedData, chunkData)) {
                    throw std::runtime_error("Failed to compress chunk data (zlib).");
                }
            } else if(compression == CompressionType::Gzip) {
                // Regions are rarely compressed with gzip. But in case it should, we can do!
                if(!deflate_gzip(serializedData, chunkData)) {
                    throw std::runtime_error("Failed to compress chunk data (zlib).");
                }
            } else if(compression == CompressionType::Uncompressed) {
                // This is super rare condition and should usually not occur. 
                // But we can also handle this.
                chunkData = std::move(serializedData);
            }

            // calculate some sizes.
            size_t length           = 1u + chunkData.size();
            size_t payload          = 4u + length;
            size_t sectorPadding    = (((payload % SectorSize) > 0) ? 1 : 0);
            size_t sectors          = payload / SectorSize + sectorPadding;
            size_t storageSize      = sectors * SectorSize;

            // Set chunk infos in region header.
            regionHeader.setChunkData(index, storageDataOffset / SectorSize, sectors, 0);

            // Write the chunk to the region data.
            regionData.resize(regionData.size() + storageSize, 0);
            length = detail::swapEndian(length);
            std::memcpy(&regionData[storageDataOffset], &length, 4u);
            std::memcpy(&regionData[storageDataOffset + 4], &compression, 1u);
            std::memcpy(&regionData[storageDataOffset + 5], chunkData.data(), chunkData.size());

            // Increase the data index to beginning of next chunk.
            storageDataOffset += storageSize;
        }
    }

    // After all chunks have been written and the chunk data has been set to the region header, 
    // we can now also write the region header data.
    std::memcpy(&regionData[0], regionHeader.headerData(), regionHeader.headerSize());

    std::ofstream stream(filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error("Failed to open file.");
    }
    stream.write(reinterpret_cast<char*>(regionData.data()), regionData.size());
    stream.close();

    return true;
}

int32_t Region::x() const
{
    return m_x;
}

int32_t Region::z() const
{
    return m_z;
}

Vec2 Region::xz() const
{
    Vec2 coord;
    coord.x = m_x;
    coord.z = m_z;
    return coord;
}

Chunk& Region::chunkAt(size_t index)
{
    checkRange(index);

    return m_chunks[index];
}

Chunk& Region::chunkAt(int32_t x, int32_t z)
{
    checkRange(x, z);

    return m_chunks[toIndex(x, z)];
}

Chunk& Region::chunkAt(const Vec2 &coord)
{
    checkRange(coord.x, coord.z);

    return m_chunks[toIndex(coord.x, coord.z)];
}

const Chunk& Region::chunkAt(size_t index) const
{
    checkRange(index);

    return m_chunks[index];
}

const Chunk& Region::chunkAt(int32_t x, int32_t z) const
{
    checkRange(x, z);

    return m_chunks[toIndex(x, z)];
}

const Chunk& Region::chunkAt(const Vec2 &coord) const
{
    checkRange(coord.x, coord.z);

    return m_chunks[toIndex(coord.x, coord.z)];
}

void Region::checkRange(int32_t x, int32_t z) const
{
    if(x < 0 || x >= ChunksPerRegionAxis
       || z < 0 || z >= ChunksPerRegionAxis) {
        throw std::out_of_range("Chunk coordinate is out of range.");
    }
}

void Region::checkRange(size_t index) const
{
    if(index >= Chunks) {
        throw std::out_of_range("Index is out of range.");
    }
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
    int32_t x = 0;
    int32_t z = 0;
    return validateAndParseRegionFilename(filename, x, z);
}

bool Region::validateAndParseRegionFilename(const std::string &filename, int32_t &x, int32_t &z)
{
    // Pattern definition of Minecraft region file.
    const std::regex RegionFilePattern 
        = std::regex("r\\.(0|[-]?[1-9][0-9]*)\\.(0|[-]?[1-9][0-9]*)\\.mca");

    // Convert filename so that preferred directory separators are used.
    std::filesystem::path filepath{filename};
    std::string convertedFilename = filepath.make_preferred().string();

    // Extract the filename from the whole path
    size_t offset = convertedFilename.find_last_of(std::filesystem::path::preferred_separator);
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

size_t Region::toIndex(int32_t x, int32_t z)
{
    return static_cast<size_t>(z) * ChunksPerRegionAxis + static_cast<size_t>(x);
}

Vec2 Region::fromIndex(size_t index)
{
    if(index >= Chunks) {
        throw std::out_of_range("Index is out of range.");
    }

    Vec2 coord;
    coord.x = index % ChunksPerRegionAxis;
    coord.z = index / ChunksPerRegionAxis;
    return coord;
}

} // namespace anvil
