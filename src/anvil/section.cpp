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
    bool hasExpectedChildren = tag->hasChild("palette");
    bool hasData             = tag->hasChild("data");
    bool childrenHaveExpectedTypes =
        tag->getChildByName("palette")->isListTag()
        && (hasData ? tag->getChildByName("data")->isLongArrayTag() : true);
    return hasExpectedChildren && childrenHaveExpectedTypes;
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
    bool hasExpectedChildren = tag->hasChild("Name");
    bool hasProperties       = tag->hasChild("Properties");
    bool hasExpectedChildrenTypes =
        tag->getChildByName("palette")->isListTag()
        && (hasProperties ? tag->getChildByName("Properties")->isCompoundTag() : true);
    return hasExpectedChildren && hasExpectedChildrenTypes;
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
    bool hasExpectedChildren = tag->hasChild("palette");
    bool hasData             = tag->hasChild("data");
    bool hasExpectedChildrenTypes =
        tag->getChildByName("palette")->isListTag()
        && (hasData ? tag->getChildByName("data")->isLongArrayTag() : true);
    return hasExpectedChildren && hasExpectedChildrenTypes;
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
    bool hasExpectedChildren =
        tag->hasChild("biomes") && tag->hasChild("block_states") && tag->hasChild("Y");
    bool hasBlockLight = tag->hasChild("BlockLight");
    bool hasExpectedChildrenTypes =
        tag->getChildByName("biomes")->isCompoundTag()
        && tag->getChildByName("block_states")->isCompoundTag()
        && tag->getChildByName("Y")->isByteTag()
        && (hasBlockLight ? tag->getChildByName("BlockLight")->isByteArrayTag() : true);
    bool childrenAreValid =
        Biomes::isValidBiomes(tag->getChildByName("biomes")->asCompoundTag())
        && BlockStates::isValidBlockStates(tag->getChildByName("block_states")->asCompoundTag());

    return hasExpectedChildren && hasExpectedChildrenTypes && childrenAreValid;
}

} // namespace anvil
