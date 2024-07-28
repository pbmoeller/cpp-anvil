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

    bool push_back(std::unique_ptr<CompoundType> value) {
        if(value) {
            m_value.push_back(std::move(value));
            return true;
        }
        return false;
    }

    bool push_back(CompoundType *value) {
        if(value) {
            m_value.push_back(std::unique_ptr<CompoundType>(value));
            return true;
        }
        return false;
    }
};

} // namespace nbt

#endif // CPP_ANVIL_NBT_COMPOUND_TAG_HPP
