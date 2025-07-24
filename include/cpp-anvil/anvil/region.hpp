#ifndef CPP_ANVIL_ANVIL_REGION_HPP
#define CPP_ANVIL_ANVIL_REGION_HPP

#include "cpp-anvil/anvil/chunk.hpp"
#include "cpp-anvil/anvil/coordinates.hpp"
#include "cpp-anvil/util/compression.hpp"

#include <array>
#include <memory>
#include <string>
#include <vector>

namespace anvil {

class RegionHeader;

//! @brief Class to store minecraft region data.
class Region
{
public:
    constexpr static size_t ChunksPerRegionAxis{32};
    constexpr static size_t Chunks{1024};
    constexpr static size_t SectorSize{4096};

public:
    //! @brief Constructs an empty region.
    Region();

    //! @brief Destroys the region object.
    ~Region();

    //! @brief Loads the complete region file.
    //! @param filename Filename of the region file to be loaded.
    void loadFromFile(const std::string &filename);

    //! @brief Loads the region file only partially.
    //! @details
    //! Partial loading of the region file means that only the region header is loaded but not the
    //! chunks.
    //! 
    //! @param filename Region filename to be loaded partially.
    void loadPartiallyFromFile(const std::string &filename);

    //! @brief Loads the chunk at specific index.
    //! @param index Index of the chunk to be loaded.
    void loadChunkAt(size_t index);

    //! @brief Loads all chunks in the region file.
    void loadAllChunks();

    //! @brief Checks if a chunk is already loaded.
    //! @param index Index of chunk to check.
    //! @return `true` if chunk is loaded, `false` if not.
    bool isChunkLoaded(size_t index) const;

    //! @brief Checks if a chunk can be loaded. 
    //! @details
    //! This functions requires that the FileHeader has been read before. This is done when 
    //! @ref loadFromFile() or @ref loadPartiallyFromFile() has been called before.
    //! 
    //! @param index Index of chunk that shoudl be checked.
    //! @return `true` if chunk can be loaded, `false` if not.
    bool isChunkLoadable(size_t index) const;

    //! @brief Saves the region to the file it has been loaded from.
    //! @return `true` if files was successfully saved, `false` otherwise.
    bool saveToFile();

    //! @brief Saves the region to the given filename.
    //! @param filename The filename where the region data should be saved.
    //! @return `true` if files was successfully saved, `false` otherwise.
    bool saveToFile(const std::string &filename);

    //! @brief Returns the x coordinate of the region.
    //! @return X coordinate.
    int32_t x() const;

    //! @brief Returns the z coordinate of the region.
    //! @return Z coordinate.
    int32_t z() const;

    //! @brief Returns coordinate of region within world.
    //! @return World coordinate of region.
    Vec2 xz() const;

    //! @brief Gets a chunk from the region via index.
    //! @param index Index of the requested chunk. Must be in range [0, 1024).
    //! @return Reference to chunk at @p index
    //! @throws std::out_of_range If index is out of range.
    Chunk& chunkAt(size_t index);

    //! @brief Gets a chunk from the region by the chunk coordinate.
    //! @param x X coordinate of chunk within region. Must be in range [0, 32).
    //! @param z Y coordinate of chunk within region. Must be in range [0, 32).
    //! @return Returns chunk at coordinate x|y.
    //! @throws std::out_of_range If x or z are out of range.
    Chunk& chunkAt(int32_t x, int32_t z);

    //! @brief Gets a chunk from the region by the chunk coordinate.
    //! @param coord Coordinate of the chunk within the region.
    //! @return Returns chunk at passed coordinate.
    Chunk& chunkAt(const Vec2 &coord);

    //! @brief Gets a chunk from the region via index. Must be in range [0, 1024).
    //! @param index Index of the requested chunk.
    //! @return Const reference to chunk at @p index
    //! @throws std::out_of_range If index is out of range.
    const Chunk& chunkAt(size_t index) const;
    
    //! @brief Gets a chunk from the region by the chunk coordinate.
    //! @param x X coordinate of chunk within region. Must be in range [0, 32).
    //! @param z Y coordinate of chunk within region. Must be in range [0, 32).
    //! @return Returns chunk at coordinate x|y.
    //! @throws std::out_of_range If x or z are out of range.
    const Chunk& chunkAt(int32_t x, int32_t z) const;

    //! @brief Gets a chunk from the region by the chunk coordinate.
    //! @param coord Coordinate of the chunk within the region.
    //! @return Returns chunk at passed coordinate.
    const Chunk& chunkAt(const Vec2 &coord) const;

private:
    //! @brief Checks that the coordinates are in valid range for chunk access.
    //! @param x X coordinate. Must be in range [0, 32).
    //! @param z Z coordinate. Must be in range [0, 32).
    void checkRange(int32_t x, int32_t z) const;

    //! @brief Checks that the index is in valid range for chunk access.
    //! @param index Index of chunk to access. Must be in range [0, 1024).
    void checkRange(size_t index) const;

    //! @brief Reads the chunkdata from @p filestream at chunk @p index 
    //! @param filestream The filestream to read the chunk data from.
    //! @param index The chunk index to be read.
    void readChunkData(std::ifstream &filestream, const size_t index);

    //! @brief Reads the region header in the region file.
    //! @param filestream The filestream to read the data from.
    //! @return `true` if the region header could be read successfully, `false` otherwise.
    bool readRegionHeader(std::ifstream &filestream);

public:
    //! @brief Checks if the filename matches a valid Minecraft region filename.
    //! @param filename The filename to be checked.
    //! @return `true` if the filename is valid, `false` otherwiese.
    static bool validateRegionFilename(const std::string &filename);

    //! @brief Checks if the filename matches a valid Minecraft region filename and 
    //!        sets the region coordinates.
    //! @param filename The filename to be checked.
    //! @param x The X coordinate of the region file.
    //! @param z The Z coordinate of the region file.
    //! @return `true` if the filename is valid, `false` otherwiese.
    static bool validateAndParseRegionFilename(const std::string &filename, int32_t &x, int32_t &z);

    //! @brief Converts chunk coordinates to chunk index.
    //! @param x X coordinate of chunk.
    //! @param z Y coordinate of chunk.
    //! @return Index of chunk.
    static size_t toIndex(int32_t x, int32_t z);

    //! @brief Converts chunk index to chunk coordinate.
    //! @param index Index of chunk.
    //! @return Coordinate of chunk.
    static Vec2 fromIndex(size_t index);

private:
    int32_t m_x{0};
    int32_t m_z{0};
    std::string m_filename;

    std::array<bool, Chunks> m_loadedChunks;
    std::array<Chunk, Chunks> m_chunks;
    std::array<CompressionType, Chunks> m_chunkCompression;

    std::unique_ptr<RegionHeader> m_regionHeader;
};

} // namespace anvil

#endif // CPP_ANVIL_ANVIL_REGION_HPP
