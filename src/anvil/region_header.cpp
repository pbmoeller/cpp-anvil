// Internal headers
#include "anvil/region_header.hpp"
#include "util/byte_swap.hpp"

namespace anvil {

bool RegionHeader::loadFromStream(std::ifstream& filestream)
{
    filestream.read(reinterpret_cast<char*>(m_data.data()), RegionHeader::HeaderSize);
    return filestream.gcount() == RegionHeader::HeaderSize;
}

const std::array<unsigned char, RegionHeader::HeaderSize>& RegionHeader::data() const
{
    return m_data;
}

const unsigned char* RegionHeader::headerData() const
{
    return m_data.data();
}

size_t RegionHeader::chunkCount() const
{
    size_t count{0};
    const uint32_t* dataAsInt = reinterpret_cast<const uint32_t*>(m_data.data());
    for(size_t index = 0; index < Chunks; ++index) {
        if(((dataAsInt[index] & 0xFFFFFF00) >> 8u) > 0u) {
            ++count;
        }
    }
    return count;
}

bool RegionHeader::empty(const size_t index) const
{
    return offset(index) == 0;
}

size_t RegionHeader::offset(const size_t index) const
{
    const uint32_t* dataAsInt = reinterpret_cast<const uint32_t*>(m_data.data());
    return ((detail::swapEndian(dataAsInt[index]) & 0xFFFFFF00) >> 8);
}

size_t RegionHeader::byteOffset(const size_t index) const
{
    return offset(index) * SectorSize;
}

size_t RegionHeader::size(const size_t index) const
{
    const uint32_t* dataAsInt = reinterpret_cast<const uint32_t*>(m_data.data());
    return (detail::swapEndian(dataAsInt[index]) & 0x000000FF);
}

size_t RegionHeader::byteSize(const size_t index) const
{
    return size(index) * SectorSize;
}

uint32_t RegionHeader::timestamp(const size_t index) const
{
    const uint32_t* dataAsInt = reinterpret_cast<const uint32_t*>(m_data.data());
    return detail::swapEndian(dataAsInt[Chunks + index]);
}

void RegionHeader::setChunkData(const size_t index, const size_t offset, const size_t size,
                                const uint32_t timestamp)
{
    uint32_t* dataAsInt = reinterpret_cast<uint32_t*>(m_data.data());
    uint32_t value      = ((static_cast<uint32_t>(offset) << 8) & 0xFFFFFF00)
                   + (static_cast<uint32_t>(size) & 0x000000FF);

    dataAsInt[index]          = detail::swapEndian(value);
    dataAsInt[Chunks + index] = detail::swapEndian(timestamp);
}

} // namespace anvil
