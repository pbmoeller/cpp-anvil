#include "cpp-anvil/anvil/section.hpp"
#include "cpp-anvil/nbt/list_tag.hpp"
#include "cpp-anvil/nbt/primitive_tag.hpp"

#include <bit>

namespace anvil {

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Biomes

ListTag* Biomes::palette() const
{
    return m_tag->getChildByName("palette")->asListTag();
}

LongArrayTag* Biomes::data() const
{
    return m_tag->getChildByName("data")->asLongArrayTag();
}

CompoundTag* Biomes::tag() const
{
    return m_tag;
}

bool Biomes::isValidBiomes(const CompoundTag* tag)
{
    auto* palette = tag->getChildByName("palette");
    auto* data    = tag->getChildByName("data");

    bool hasExpectedChildren = palette;
    bool hasExpectedTypes    = palette->isListTag() && (!data || data->isLongArrayTag());

    return hasExpectedChildren && hasExpectedTypes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// BlockStates

StringType BlockState::name() const
{
    return m_tag->getChildByName("Name")->asStringTag()->value();
}

CompoundTag* BlockState::properties() const
{
    auto* props = m_tag->getChildByName("properties");
    if(props) {
        return props->asCompoundTag();
    }
    return nullptr;
}

CompoundTag* BlockState::tag() const
{
    return m_tag;
}

bool BlockState::isValidBlockState(const CompoundTag* tag)
{
    auto* name       = tag->getChildByName("Name");
    auto* properties = tag->getChildByName("properties");

    bool hasExpectedChildren = name;
    bool hasExpectedTypes    = name->isStringTag() && (!properties || properties->isCompoundTag());

    return hasExpectedChildren && hasExpectedTypes;
}

BlockData::BlockData(const LongArrayTag* tag, int bitWidth)
    : m_data{}
{
    constexpr int LongSize  = sizeof(LongType);
    const int blocksPerLong = LongSize / bitWidth;

    size_t blockIndex = 0;
    for(size_t i = 0; i < tag->size(); ++i) {
        LongType value = (*tag)[i];
        for(int j = 0; j < blocksPerLong; ++j) {
            m_data[blockIndex / BlocksPerSectionLayer][blockIndex / SectionSizeX % SectionSizeZ]
                  [blockIndex % SectionSizeX] =
                      static_cast<uint16_t>(value & ((1 << bitWidth) - 1));
            value >>= bitWidth;
            ++blockIndex;
        }
    }
}

ListTag* BlockStates::palette() const
{
    return m_tag->getChildByName("palette")->asListTag();
}

BlockState BlockStates::paletteAt(size_t index) const
{
    auto p = palette();
    if(index >= p->size()) {
        throw std::out_of_range("Section index is out of range.");
    }
    return BlockState((*p)[index]->asCompoundTag());
}

LongArrayTag* BlockStates::data() const
{
    return m_tag->getChildByName("data")->asLongArrayTag();
}

BlockData BlockStates::blockData() const
{
    return BlockData(data(), bitWidth());
}

int BlockStates::bitWidth() const
{
    return std::bit_width(palette()->size() - 1);
}

CompoundTag* BlockStates::tag() const
{
    return m_tag;
}

bool BlockStates::isValidBlockStates(const CompoundTag* tag)
{
    auto* palette = tag->getChildByName("palette");
    auto* data    = tag->getChildByName("data");

    bool hasExpectedChildren = palette;
    bool hasExpectedTypes    = palette->isListTag() && (!data || data->isLongArrayTag());

    return hasExpectedChildren && hasExpectedTypes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Section

Biomes Section::biomes() const
{
    return Biomes(m_tag->getChildByName("biomes")->asCompoundTag());
}

BlockStates Section::blockStates() const
{
    return BlockStates(m_tag->getChildByName("block_states")->asCompoundTag());
}

ByteArrayTag* Section::blockLight() const
{
    return m_tag->getChildByName("BlockLight")->asByteArrayTag();
}

ByteArrayTag* Section::skyLight() const
{
    return m_tag->getChildByName("SkyLight")->asByteArrayTag();
}

ByteType Section::y() const
{
    return m_tag->getChildByName("Y")->asByteTag()->value();
}

CompoundTag* Section::tag() const
{
    return m_tag;
}

bool Section::isValidSection(const CompoundTag* tag)
{
    auto* y           = tag->getChildByName("Y");
    auto* biomes      = tag->getChildByName("biomes");
    auto* blockStates = tag->getChildByName("block_states");
    auto* blockLight  = tag->getChildByName("BlockLight");
    auto* skyLight    = tag->getChildByName("SkyLight");

    bool hasExpectedChildren = y;

    bool hasExpectedTypes = y->isByteTag() && (!biomes || biomes->isCompoundTag())
                         && (!blockStates || blockStates->isCompoundTag())
                         && (!blockLight || blockLight->isByteArrayTag())
                         && (!skyLight || skyLight->isByteArrayTag());
    bool childrenAreValid =
        (!biomes || Biomes::isValidBiomes(biomes->asCompoundTag()))
        && (!blockStates || BlockStates::isValidBlockStates(blockStates->asCompoundTag()));

    return hasExpectedChildren && hasExpectedTypes && childrenAreValid;
}

} // namespace anvil
