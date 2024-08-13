#ifndef CPP_ANVIL_NBT_LIST_TAG_HPP
#define CPP_ANVIL_NBT_LIST_TAG_HPP

// cpp-anvil
#include <cpp-anvil/nbt/collection_tag.hpp>
#include <cpp-anvil/nbt/types.hpp>

// STL
#include <stdexcept>

namespace anvil {

// -------------------------------------------------------------------------------------------------
//      ListTag
// -------------------------------------------------------------------------------------------------

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

    bool push_back(std::unique_ptr<BasicTag> value) {
        if(value) {
            if(empty()) {
                m_listType = value->type();
            }
            if(value->type() == m_listType) {
                m_value.push_back(std::move(value));
                return true;
            }
        }
        return false;
    }

    bool push_back(BasicTag *value) {
        if(value) {
            if(empty()) {
                m_listType = value->type();
            }
            if(value->type() == m_listType) {
                m_value.push_back(std::unique_ptr<BasicTag>(value));
                return true;
            }
        }
        return false;
    }

    bool push_back(const BasicTag &value) {
        if(empty()) {
            m_listType = value.type();
        }
        if(value.type() == m_listType) {
            m_value.push_back(value.clone());
            return true;
        }
        return false;
    }

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
