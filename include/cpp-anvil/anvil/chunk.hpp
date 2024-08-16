#ifndef CPP_ANVIL_ANVIL_CHUNK_HPP
#define CPP_ANVIL_ANVIL_CHUNK_HPP

// cpp-anvil
#include <cpp-anvil/nbt.hpp>

// STL
#include <memory>

namespace anvil {

class Chunk
{
public:

    void clear();
    bool empty() const;

    CompoundTag* getRootTag();
    const CompoundTag* getRootTag() const;

    void setRootTag(std::unique_ptr<CompoundTag> root);
    std::unique_ptr<CompoundTag> takeRootTag();

private:
    std::unique_ptr<CompoundTag> m_root;
};

} // namespace anvil

#endif // CPP_ANVIL_ANVIL_CHUNK_HPP
