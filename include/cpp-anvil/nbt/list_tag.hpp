#ifndef CPP_ANVIL_NBT_LIST_TAG_HPP
#define CPP_ANVIL_NBT_LIST_TAG_HPP

// cpp-anvil
#include <cpp-anvil/nbt/collection_tag.hpp>
#include <cpp-anvil/nbt/types.hpp>

namespace nbt {

// -------------------------------------------------------------------------------------------------
//      ListTag
// -------------------------------------------------------------------------------------------------

class ListTag : public CollectionTag<ListType, TagType::List>
{
public:
    ListTag() = default;
    ListTag(const ListTag &other) = default;
    ListTag(ListTag &&other) noexcept = default;
    explicit ListTag(const std::string &name)
        : CollectionTag(name) {}
    explicit ListTag(const ContainerType<value_type> &value)
        : CollectionTag(value) {}
    explicit ListTag(const std::string &name, const ContainerType<value_type> &value) noexcept
        : CollectionTag(name, value) {}
    virtual ~ListTag() = default;

    ListTag& operator=(const ListTag &other) = default;
    ListTag& operator=(ListTag &&other) noexcept = default;

    virtual std::unique_ptr<BasicTag> clone() const override {
        return std::make_unique<ListTag>(*this);
    }
};

} // namespace nbt

#endif // CPP_ANVIL_NBT_LIST_TAG_HPP