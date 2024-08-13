#ifndef CPP_ANVIL_ANVIL_REGION_HEADER_HPP
#define CPP_ANVIL_ANVIL_REGION_HEADER_HPP

// STL
#include <array>
#include <fstream>

namespace anvil {

class RegionHeader
{
public:
    constexpr static size_t HeaderSize{8192};
    constexpr static size_t Chunks{1024};
    constexpr static size_t SectorSize{4096};

public:
    bool loadFromStream(std::ifstream &filestream);

    const std::array<unsigned char, HeaderSize>& data() const;

    size_t chunkCount() const;

    bool empty(const size_t index) const;

    size_t offset(const size_t index) const;
    size_t byteOffset(const size_t index) const;

    size_t size(const size_t index) const;
    size_t byteSize(const size_t index) const;

    uint32_t timestamp(const size_t index) const;

    void setChunkData(const size_t index,
                      const size_t offset,
                      const size_t size,
                      const uint32_t timestamp);

private:
    std::array<unsigned char, HeaderSize> m_data{};
};

} // namespace anvil

#endif // CPP_ANVIL_ANVIL_REGION_HEADER_HPP
