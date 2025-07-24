#ifndef CPP_ANVIL_NBT_LIST_TAG_HPP
#define CPP_ANVIL_NBT_LIST_TAG_HPP

#include "cpp-anvil/nbt/collection_tag.hpp"
#include "cpp-anvil/nbt/types.hpp"

#include <stdexcept>

namespace anvil {

class ListTag : public CollectionTag<std::unique_ptr<BasicTag>, TagType::List>
{
public:
    ListTag() = default;
    ListTag(const ListTag &other) = default;
    ListTag(ListTag &&other) noexcept = default;
    explicit ListTag(const std::string &name)
        : CollectionTag(name) {}
    explicit ListTag(const std::string &name, TagType listTagType)
        : CollectionTag(name)
        , m_listType(listTagType) {}
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

    constexpr TagType listType() const {
        return m_listType;
    }

    bool push_back(std::unique_ptr<BasicTag> value);
    bool push_back(BasicTag *value);
    bool push_back(const BasicTag &value);

    std::unique_ptr<BasicTag> takeAt(size_type index);
    std::unique_ptr<BasicTag> take(BasicTag *tag);

    bool erase(BasicTag *tag);

protected:
    virtual bool isEqual(const BasicTag &other) const override
    {
        const ListTag &otherTag = static_cast<const ListTag&>(other);
        return m_listType == otherTag.m_listType
            && CollectionTag::isEqual(other);
    }

private:
    TagType m_listType{TagType::End};
};

} // namespace anvil

#endif // CPP_ANVIL_NBT_LIST_TAG_HPP
