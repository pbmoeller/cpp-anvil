// cpp-anvil
#include <cpp-anvil/anvil/region.hpp>

#include "anvil/region_header.hpp"

// STL
#include <regex>
#include <fstream>
#include <filesystem>

namespace anvil {

Region::Region() = default;

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

void Region::loadChunkAt(int index)
{

}

void Region::loadAllChunks()
{

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
