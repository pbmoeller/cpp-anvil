#ifndef CPP_ANVIL_ANVIL_CHUNK_HPP
#define CPP_ANVIL_ANVIL_CHUNK_HPP

// STL
#include <memory>

namespace anvil {

class CompoundTag;

//! @brief Class to store minecraft chunk data.
class Chunk
{
public:
    //! @brief Resets the chunk data.
    void clear();

    //! @brief Returns whether the chunk is empty.
    //! 
    //! @return `true` if chunk is empty, `false` otherwise.
    bool empty() const;

    //! @brief Returns a pointer to the root CompoundTag of the chunk.
    //! 
    //! @return Pointer to stored root CompoundTag, `nullptr` is root tag is empty.
    CompoundTag* rootTag();

    //! @brief Returns a const pointer to the root CompoundTag of the chunk.
    //! 
    //! @return Const pointer to stored root CompoundTag, `nullptr` is root tag is empty.
    const CompoundTag* rootTag() const;

    //! @brief Sets a new root CompoundTag to the chunk.
    //! 
    //! If a root tag is already set, it will be reset during this operation.
    //! 
    //! @param root The new CompoundTag to be be set.
    void setRootTag(std::unique_ptr<CompoundTag> root);

    //! @brief Takes ownership of the root CompoundTag.
    //! 
    //! The chunk is empty after this operation.
    //! 
    //! @return The chunks root CompoundTag.
    std::unique_ptr<CompoundTag> takeRootTag();

private:
    std::unique_ptr<CompoundTag> m_root;
};

} // namespace anvil

#endif // CPP_ANVIL_ANVIL_CHUNK_HPP
