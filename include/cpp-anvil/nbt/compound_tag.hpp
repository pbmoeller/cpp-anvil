#ifndef CPP_ANVIL_NBT_COMPOUND_TAG_HPP
#define CPP_ANVIL_NBT_COMPOUND_TAG_HPP

// cpp-anvil
#include <cpp-anvil/nbt/collection_tag.hpp>
#include <cpp-anvil/nbt/types.hpp>

namespace nbt {

// -------------------------------------------------------------------------------------------------
//      CompoundTag
// -------------------------------------------------------------------------------------------------

class CompoundTag : public CollectionTag<std::unique_ptr<CompoundType>, TagType::Compound>
{
public:
    CompoundTag() = default;
    CompoundTag(const CompoundTag &other) = default;
    CompoundTag(CompoundTag &&other) noexcept = default;
    explicit CompoundTag(const std::string &name)
        : CollectionTag(name) {}
    explicit CompoundTag(const ContainerType<value_type> &value)
        : CollectionTag(value) {}
     explicit CompoundTag(const std::string &name, const ContainerType<value_type> &value) noexcept
         : CollectionTag(name, value) {}
    virtual ~CompoundTag() = default;

    CompoundTag& operator=(const CompoundTag &other) = default;
    CompoundTag& operator=(CompoundTag &&other) noexcept = default;

    virtual std::unique_ptr<BasicTag> clone() const override {
        return std::make_unique<CompoundTag>(*this);
    }
};

} // namespace nbt

#endif // CPP_ANVIL_NBT_COMPOUND_TAG_HPP