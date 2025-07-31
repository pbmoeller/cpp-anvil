#include "cpp-anvil/anvil/chunk.hpp"
#include "cpp-anvil/nbt/compound_tag.hpp"
#include "cpp-anvil/nbt/list_tag.hpp"
#include "cpp-anvil/nbt/primitive_tag.hpp"

namespace anvil {

void Chunk::clear()
{
    m_root.reset();
}

bool Chunk::empty() const
{
    return m_root == nullptr;
}

CompoundTag* Chunk::rootTag()
{
    return m_root.get();
}

const CompoundTag* Chunk::rootTag() const
{
    return m_root.get();
}

void Chunk::setRootTag(std::unique_ptr<CompoundTag> root)
{
    m_root = std::move(root);
}

std::unique_ptr<CompoundTag> Chunk::takeRootTag()
{
    return std::move(m_root);
}

IntType Chunk::xPos() const
{
    return m_root->getChildByName("xPos")->asIntTag()->value();
}

IntType Chunk::yPos() const
{
    return m_root->getChildByName("yPos")->asIntTag()->value();
}

IntType Chunk::zPos() const
{
    return m_root->getChildByName("zPos")->asIntTag()->value();
}

IntType Chunk::dataVersion() const
{
    return m_root->getChildByName("DataVersion")->asIntTag()->value();
}

LongType Chunk::inhabitedTime() const
{
    return m_root->getChildByName("InhabitedTime")->asLongTag()->value();
}

ByteType Chunk::isLightOn() const
{
    return m_root->getChildByName("isLightOn")->asByteTag()->value();
}

LongType Chunk::lastUpdate() const
{
    return m_root->getChildByName("LastUpdate")->asLongTag()->value();
}

StringType Chunk::status() const
{
    return m_root->getChildByName("Status")->asStringTag()->value();
}

CompoundTag* Chunk::heightMaps() const
{
    return m_root->getChildByName("Heightmaps")->asCompoundTag();
}

CompoundTag* Chunk::structures() const
{
    return m_root->getChildByName("structures")->asCompoundTag();
}

ListTag* Chunk::blockEntities() const
{
    return m_root->getChildByName("block_entities")->asListTag();
}

ListTag* Chunk::blockTicks() const
{
    return m_root->getChildByName("block_ticks")->asListTag();
}

ListTag* Chunk::fluidTicks() const
{
    return m_root->getChildByName("fluid_ticks")->asListTag();
}

ListTag* Chunk::postProcessing() const
{
    return m_root->getChildByName("PostProcessing")->asListTag();
}

ListTag* Chunk::sections() const
{
    return m_root->getChildByName("Sections")->asListTag();
}

Section Chunk::section(size_t index) const
{
    if(index >= SectionsPerChunk) {
        throw std::out_of_range("Section index is out of range.");
    }
    return Section((*sections())[index]->asCompoundTag());
}

} // namespace anvil
