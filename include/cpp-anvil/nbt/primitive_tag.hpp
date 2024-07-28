#ifndef CPP_ANVIL_NBT_PRIMITIVE_TAG_HPP
#define CPP_ANVIL_NBT_PRIMITIVE_TAG_HPP

// cpp-anvil
#include <cpp-anvil/nbt/basic_tag.hpp>
#include <cpp-anvil/nbt/types.hpp>
#include <cpp-anvil/nbt/detail/math.hpp>

namespace nbt {

// -------------------------------------------------------------------------------------------------
//      PrimitiveTag
// -------------------------------------------------------------------------------------------------

template<typename T, TagType TAG>
class PrimitiveTag : public NamedTag
{
public:
    using value_type = T;

    enum { Type = static_cast<int>(TAG) };

public:
    PrimitiveTag() = default;
    PrimitiveTag(const PrimitiveTag &other) = default;
    PrimitiveTag(PrimitiveTag &&other) noexcept = default;
    explicit PrimitiveTag(const std::string &name) requires(!detail::IsStringType<T>)
        : NamedTag(name) {};
    explicit PrimitiveTag(const T &value)
        : NamedTag(), m_value(value) {};
    explicit PrimitiveTag(const std::string &name, const T &value) noexcept
        : NamedTag(name), m_value(value) {};
    virtual ~PrimitiveTag() = default;

    PrimitiveTag& operator=(const PrimitiveTag &other) = default;
    PrimitiveTag& operator=(PrimitiveTag &&other) noexcept = default;

    constexpr virtual TagType type() const { return TAG; }

    virtual std::unique_ptr<BasicTag> clone() const override {
        return std::make_unique<PrimitiveTag<T, TAG>>(*this);
    }

    T value() const { return m_value; }
    const T& value() const requires(detail::IsStringType<T>) { return m_value; }
    void setValue(const T &value) { m_value = value; }

protected:
    virtual bool isEqual(const BasicTag &other) const override
    {
        const PrimitiveTag<T, TAG> &otherTag = static_cast<const PrimitiveTag<T, TAG>&>(other);

        return NamedTag::isEqual(other)
            && m_value == otherTag.m_value;
    }

private:
    T m_value{};
};

using ByteTag   = PrimitiveTag<ByteType,    TagType::Byte>;
using ShortTag  = PrimitiveTag<ShortType,   TagType::Short>;
using IntTag    = PrimitiveTag<IntType,     TagType::Int>;
using LongTag   = PrimitiveTag<LongType,    TagType::Long>;
using FloatTag  = PrimitiveTag<FloatType,   TagType::Float>;
using DoubleTag = PrimitiveTag<DoubleType,  TagType::Double>;
using StringTag = PrimitiveTag<StringType,  TagType::String>;

// -------------------------------------------------------------------------------------------------
//      FloatingPoint comparison
// -------------------------------------------------------------------------------------------------

template<>
inline bool FloatTag::isEqual(const BasicTag &other) const
{
    const FloatTag &otherTag = static_cast<const FloatTag&>(other);
    return NamedTag::isEqual(other)
        && detail::almostEqualUlps(m_value, otherTag.m_value, 10);
}

template<>
inline bool DoubleTag::isEqual(const BasicTag &other) const
{
    const DoubleTag &otherTag = static_cast<const DoubleTag&>(other);
    return NamedTag::isEqual(other)
        && detail::almostEqualUlps(m_value, otherTag.m_value, 10LL);
}

} // namespace nbt

#endif // CPP_ANVIL_NBT_PRIMITIVE_TAG_HPP
