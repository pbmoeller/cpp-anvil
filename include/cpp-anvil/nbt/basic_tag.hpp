#ifndef CPP_ANVIL_NBT_BASIC_TAG_HPP
#define CPP_ANVIL_NBT_BASIC_TAG_HPP

// cpp-anvil
#include <cpp-anvil/nbt/types.hpp>

// STL
#include <typeinfo>
#include <type_traits>
#include <memory>

namespace nbt {

// -------------------------------------------------------------------------------------------------
//      BasicTag
// -------------------------------------------------------------------------------------------------

class BasicTag
{
public:
    enum { Type = static_cast<int>(TagType::Unknown) };

public:
    BasicTag() = default;
    BasicTag(const BasicTag &other) = default;
    BasicTag(BasicTag &&other) noexcept = default;
    virtual ~BasicTag() = default;

    BasicTag& operator=(const BasicTag &other) = default;
    BasicTag& operator=(BasicTag &&other) noexcept = default;

    constexpr virtual TagType type() const {
        return TagType::Unknown;
    }

    virtual std::unique_ptr<BasicTag> clone() const = 0;

    // virtual std::vector<unsigned char> data() = 0;

protected:
    virtual bool isEqual(const BasicTag &other) const {
        if(this == &other) {
            return true;
        }
        return type() == other.type();
    }

    friend bool operator==(const BasicTag &lhs, const BasicTag &rhs) {
        return &lhs == &rhs
            || (typeid(lhs) == typeid(rhs) && lhs.isEqual(rhs));
    }
    friend bool operator!=(const BasicTag &lhs,
                           const BasicTag &rhs) {
        return !(lhs == rhs);
    }
};

template<typename T>
inline T tag_cast(BasicTag *item)
{
    typedef typename std::remove_cv<typename std::remove_pointer<T>::type>::type Item;
    return int(Item::Type) == int(BasicTag::Type)
        || (item && int(Item::Type) == int(item->type())) ? static_cast<T>(item) : nullptr;
}

template<typename T>
inline T tag_cast(const BasicTag *item)
{
    typedef typename std::remove_cv<typename std::remove_pointer<T>::type>::type Item;
    return int(Item::Type) == int(BasicTag::Type)
        || (item && int(Item::Type) == int(item->type())) ? static_cast<T>(item) : nullptr;
}

template<typename T>
inline std::unique_ptr<T> tag_cast(std::unique_ptr<BasicTag> &&item)
{
    typedef typename std::remove_cv<typename std::remove_pointer<T>::type>::type Item;
    if(int(T::Type) == int(Item::Type)
       || (item && int(T::Type) == int(item->type()))) {
        T *t = static_cast<T*>(item.release());
        return std::unique_ptr<T>(t);
    }
    return nullptr;
}

// -------------------------------------------------------------------------------------------------
//      EndTag
// -------------------------------------------------------------------------------------------------

class EndTag : public BasicTag
{
public:
    enum { Type = static_cast<int>(TagType::End) };

public:
    constexpr virtual TagType type() const {
        return TagType::End;
    }

    virtual std::unique_ptr<BasicTag> clone() const override {
        return std::make_unique<EndTag>(*this);
    }
};

// -------------------------------------------------------------------------------------------------
//      NamedTag
// -------------------------------------------------------------------------------------------------

class NamedTag : public BasicTag
{
public:
    enum { Type = static_cast<int>(TagType::Unknown) };

public:
    NamedTag() = default;
    NamedTag(const NamedTag &other) = default;
    NamedTag(NamedTag &&other) noexcept = default;
    explicit NamedTag(const std::string &name) 
        : BasicTag(), m_name(name) {};
    explicit NamedTag(std::string &&name) noexcept
        : BasicTag(), m_name(std::move(name)) {};
    virtual ~NamedTag() = default;

    NamedTag& operator=(const NamedTag &other) = default;
    NamedTag& operator=(NamedTag &&other) noexcept = default;

    constexpr virtual TagType type() const {
        return TagType::Unknown;
    }

    std::string name() { return m_name; }
    const std::string& name() const { return m_name; }
    void setName(const std::string &name) { m_name = name; }

protected:
    virtual bool isEqual(const BasicTag &other) const override {
        const NamedTag &otherTag = static_cast<const NamedTag&>(other);
        return BasicTag::isEqual(other)
            && m_name == otherTag.m_name;
    }

private:
    std::string m_name;
};

} // namespace nbt

#endif // CPP_ANVIL_NBT_BASIC_TAG_HPP
