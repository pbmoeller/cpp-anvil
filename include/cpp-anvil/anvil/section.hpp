#ifndef CPP_ANVIL_ANVIL_SECTION_HPP
#define CPP_ANVIL_ANVIL_SECTION_HPP

#include "cpp-anvil/nbt/compound_tag.hpp"
#include "cpp-anvil/nbt/types.hpp"

#include <array>

namespace anvil {

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Biomes

class Biomes
{
public:
    explicit Biomes(CompoundTag* tag)
        : m_tag(tag)
    { }

    ListTag* palette() const;
    LongArrayTag* data() const;

    CompoundTag* tag() const;

    static bool isValidBiomes(const CompoundTag* tag);

private:
    CompoundTag* m_tag{nullptr};
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// BlockStates

class BlockState
{
public:
    explicit BlockState(CompoundTag* tag)
        : m_tag(tag)
    { }

    StringType name() const;
    CompoundTag* properties() const;

    CompoundTag* tag() const;

    static bool isValidBlockState(const CompoundTag* tag);

private:
    CompoundTag* m_tag{nullptr};
};

class BlockData
{
    constexpr static size_t SectionWidth{16};   // X
    constexpr static size_t SectionDepth{16};   // Z
    constexpr static size_t SectionHeight{16};  // Y

    constexpr static size_t SectionSizeX = SectionWidth;
    constexpr static size_t SectionSizeZ = SectionDepth;
    constexpr static size_t SectionSizeY = SectionHeight;

    constexpr static size_t BlocksPerSectionLayer{SectionWidth * SectionDepth};
    constexpr static size_t BlocksPerSection{SectionWidth * SectionDepth * SectionHeight};

public:
    explicit BlockData(const LongArrayTag* tag, int bitWidth);

private:
    std::array<std::array<std::array<uint16_t, SectionWidth>, SectionDepth>, SectionHeight>
        m_data;
};

class BlockStates
{
public:
    explicit BlockStates(CompoundTag* tag)
        : m_tag(tag)
    { }

    ListTag* palette() const;
    BlockState paletteAt(size_t index) const;
    LongArrayTag* data() const;
    BlockData blockData() const;

    int bitWidth() const;

    CompoundTag* tag() const;

    static bool isValidBlockStates(const CompoundTag* tag);

private:
    CompoundTag* m_tag{nullptr};
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Section

class Section
{
public:
    explicit Section(CompoundTag* tag)
        : m_tag(tag)
    { }

    Biomes biomes() const;
    BlockStates blockStates() const;
    ByteArrayTag* blockLight() const;
    ByteArrayTag* skyLight() const;
    ByteType y() const;

    CompoundTag* tag() const;

    static bool isValidSection(const CompoundTag *tag);

private:
    CompoundTag* m_tag{nullptr};
};

} // namespace anvil

#endif // CPP_ANVIL_ANVIL_SECTION_HPP
