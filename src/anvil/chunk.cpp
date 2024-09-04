//cpp-anvil
#include <cpp-anvil/anvil/chunk.hpp>


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

} // namespace anvil
