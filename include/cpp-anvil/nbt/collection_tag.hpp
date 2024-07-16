#ifndef CPP_ANVIL_NBT_COLLECTION_TAG_HPP
#define CPP_ANVIL_NBT_COLLECTION_TAG_HPP

// cpp-anvil
#include <cpp-anvil/nbt/basic_tag.hpp>
#include <cpp-anvil/nbt/types.hpp>

namespace nbt {

// -------------------------------------------------------------------------------------------------
//      CollectionTag
// -------------------------------------------------------------------------------------------------

template<typename T, TagType TAG>
class CollectionTag : public NamedTag
{
public:
    using value_type        = T;
    using size_type         = typename ContainerType<T>::size_type;
    using difference_type   = typename ContainerType<T>::difference_type;
    using pointer           = typename ContainerType<T>::pointer;
    using const_pointer     = typename ContainerType<T>::const_pointer;
    using reference         = T&;
    using const_reference   = const T&;

    using iterator          = typename ContainerType<T>::iterator;
    using const_iterator    = typename ContainerType<T>::const_iterator;

    using reverse_iterator          = typename ContainerType<T>::reverse_iterator;
    using const_reverse_iterator    = typename ContainerType<T>::const_reverse_iterator;

    enum { Type = static_cast<int>(TAG) };

public:
    CollectionTag() = default;
    CollectionTag(const CollectionTag &other)
        : NamedTag(other)
    {
        copy(other.m_value);
    }
    CollectionTag(CollectionTag &&other) noexcept = default;
    explicit CollectionTag(const std::string &name)
        : NamedTag(name) {};
    explicit CollectionTag(const ContainerType<T> &value)
        : NamedTag()
    {
        copy(value);
    }
    explicit CollectionTag(const std::string &name, const ContainerType<T> &value) noexcept
        : NamedTag(name)
    {
        copy(value);
    }
    virtual ~CollectionTag() = default;

    CollectionTag& operator=(const CollectionTag &other) = default;
    CollectionTag& operator=(CollectionTag &&other) noexcept = default;

    constexpr virtual TagType type() const { return TAG; }

    virtual std::unique_ptr<BasicTag> clone() const override {
        return std::make_unique<CollectionTag<T, TAG>>(*this);
    }

    ContainerType<T>& value() { return m_value; }
    const ContainerType<T>& value() const { return m_value; }
    void setValue(const ContainerType<T> &value) { copy(value); }

    // Element access
    constexpr reference at(size_type pos) { return m_value.at(pos); }
    constexpr const_reference at(const size_type pos) const { return m_value.at(pos); }

    constexpr reference operator[](size_type pos) { return m_value[pos]; }
    constexpr const_reference operator[](size_type pos) const { return m_value[pos]; }

    constexpr reference front() { return m_value.front(); }
    constexpr const_reference front() const { return m_value.front(); }

    constexpr reference back() { return m_value.back(); }
    constexpr const_reference back() const { return m_value.back(); }

    // Capacity
    constexpr bool empty() const noexcept { return m_value.empty(); }
    constexpr size_type size() const noexcept { return m_value.size(); }

    // Modifiers
    constexpr void clear() { m_value.clear(); }

    //
    void copy(const ContainerType<T> &otherValue)
    {
        if constexpr(detail::IsUniquePtr_v<T>) {
            clear();

            // Resize container to other size
            m_value.resize(otherValue.size());

            // Clone other data elements
            for(size_t i = 0; i < otherValue.size(); ++i) {
                m_value[i] = std::move(otherValue[i]->clone());
            }
        } else {
            m_value = otherValue;
        }
    }

    constexpr bool push_back(const T& value) { 
        m_value.push_back(value);
        return true;
    }
    constexpr bool push_back(T&& value) {
        m_value.push_back(std::move(value));
        return true;
    };

protected:
    virtual bool isEqual(const BasicTag &other) const override
    {
        const CollectionTag<T, TAG> &otherTag = static_cast<const CollectionTag<T, TAG>&>(other);
        return NamedTag::isEqual(other)
            && m_value == m_value;
    }

protected:
    ContainerType<T> m_value{};
};

using ByteArrayTag  = CollectionTag<ByteType,    TagType::ByteArray>;
using IntArrayTag   = CollectionTag<IntType,     TagType::IntArray>;
using LongArrayTag  = CollectionTag<LongType,    TagType::LongArray>;

} // namespace nbt

#endif // CPP_ANVIL_NBT_COLLECTION_TAG_HPP
