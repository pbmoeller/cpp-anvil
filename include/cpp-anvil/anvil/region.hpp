#ifndef CPP_ANVIL_ANVIL_REGION_HPP
#define CPP_ANVIL_ANVIL_REGION_HPP

// cpp-anvil
#include <cpp-anvil/anvil/chunk.hpp>

// STL
#include <string>
#include <vector>
#include <memory>
#include <array>

namespace anvil {

class RegionHeader;

class Region
{
public:
    constexpr static size_t Chunks{1024};
    constexpr static size_t SectorSize{4096};

public:
    //! @brief Constructs an empty region.
    Region();

    //! @brief Loads the complete region file.
    //! 
    //! @param filename Filename of the region file to be loaded.
    void loadFromFile(const std::string &filename);

    //! @brief Loads the region file only partially.
    //! 
    //! Partial loading of the region file means that only the region header is loaded but not the
    //! chunks.
    //! 
    //! @param filename Region filename to be loaded partially.
    void loadPartiallyFromFile(const std::string &filename);

    //! @brief Loads the chunk at specific index.
    //! 
    //! @param index Index of the chunk to be loaded.
    void loadChunkAt(size_t index);

    //! @brief Loads all chunks in the region file.
    void loadAllChunks();

    //! @brief Checks if a chunk is already loaded.
    //! 
    //! @param index Index of chunk to check.
    //! 
    //! @return `true` if chunk is loaded, `false` if not.
    bool isChunkLoaded(size_t index) const;

    //! @brief Checks if a chunk can be loaded. 
    //! 
    //! This functions requires that the FileHeader has been read before. This is done when 
    //! @ref loadFromFile() or @ref loadPartiallyFromFile() has been called before.
    //! 
    //! @param index Index of chunk that shoudl be checked.
    //! 
    //! @return `true` if chunk can be loaded, `false` if not.
    bool isChunkLoadable(size_t index) const;

    //! @brief Saves the region to the file it has been loaded from.
    //! 
    //! @return `true` if files was successfully saved, `false` otherwise.
    bool saveToFile();

    //! @brief Saves the region to the given filename.
    //! 
    //! @param filename The filename where the region data should be saved.
    //! 
    //! @return `true` if files was successfully saved, `false` otherwise.
    bool saveToFile(const std::string &filename);

    //! @brief Gets a chunk from the region.
    //! 
    //! @param index Index of the requested chunk.
    //! 
    //! @return Reference to chunk at \p index
    Chunk& chunkAt(size_t index);

    //! @brief Gets a chunk from the region.
    //! 
    //! @param index Index of the requested chunk.
    //! 
    //! @return Const reference to chunk at \p index
    const Chunk& chunkAt(size_t index) const;

private:
    //! @brief Reads the chunkdata from \p filestream at chunk \p index 
    //! 
    //! @param filestream  The filestream to read the chunk data from.
    //! @param index       The chunk index to be read.
    void readChunkData(std::ifstream &filestream, const size_t index);

    //! @brief Reads the region header in the region file.
    //! 
    //! @param filestream The filestream to read the data from.
    //! 
    //! @return `true` if the region header could be read successfully, `false` otherwise.
    bool readRegionHeader(std::ifstream &filestream);

public:
    //! @brief Checks if the filename matches a valid Minecraft region filename.
    //! 
    //! @param filename The filename to be checked.
    //! 
    //! @return `true` if the filename is valid, `false` otherwiese.
    static bool validateRegionFilename(const std::string &filename);

    //! @brief Checks if the filename matches a valid Minecraft region filename and 
    //!        sets the region coordinates.
    //! 
    //! @param filename The filename to be checked.
    //! @param x        The X coordinate of the region file.
    //! @param z        The Z coordinate of the region file.
    //! 
    //! @return `true` if the filename is valid, `false` otherwiese.
    static bool validateAndParseRegionFilename(const std::string &filename, int &x, int &z);

private:
    int m_x{0};
    int m_z{0};
    std::string m_filename;

    std::array<bool, Chunks> m_loadedChunks;
    std::array<Chunk, Chunks> m_chunks;
    std::array<CompressionType, Chunks> m_chunkCompression;

    std::unique_ptr<RegionHeader> m_regionHeader;
};

} // namespace anvil

#endif // CPP_ANVIL_ANVIL_REGION_HPP
