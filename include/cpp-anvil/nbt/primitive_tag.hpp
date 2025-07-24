#ifndef CPP_ANVIL_NBT_PRIMITIVE_TAG_HPP
#define CPP_ANVIL_NBT_PRIMITIVE_TAG_HPP

#include "cpp-anvil/nbt/basic_tag.hpp"
#include "cpp-anvil/nbt/detail/floating_point.hpp"
#include "cpp-anvil/nbt/types.hpp"

namespace anvil {

template<typename T, TagType TAG>
class PrimitiveTag : public BasicTag
{
public:
    using value_type = T;

    enum { Type = static_cast<int>(TAG) };

public:
    PrimitiveTag() = default;
    PrimitiveTag(const PrimitiveTag &other) = default;
    PrimitiveTag(PrimitiveTag &&other) noexcept = default;
    explicit PrimitiveTag(const std::string &name) requires(!detail::IsStringType<T>)
        : BasicTag(name) {};
    explicit PrimitiveTag(const T &value)
        : BasicTag(), m_value(value) {};
    explicit PrimitiveTag(const std::string &name, const T &value) noexcept
        : BasicTag(name), m_value(value) {};
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

        return BasicTag::isEqual(other)
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

////////////////////////////////////////////////////////////////////////////////////////////////////
// FloatingPoint comparison

template<>
inline bool FloatTag::isEqual(const BasicTag &other) const
{
    const FloatTag &otherTag = static_cast<const FloatTag&>(other);
    return BasicTag::isEqual(other)
        && detail::almostEqual<FloatType>(m_value, otherTag.m_value);
}

template<>
inline bool DoubleTag::isEqual(const BasicTag &other) const
{
    const DoubleTag &otherTag = static_cast<const DoubleTag&>(other);
    return BasicTag::isEqual(other)
        && detail::almostEqual<DoubleType>(m_value, otherTag.m_value);
}

} // namespace anvil

#endif // CPP_ANVIL_NBT_PRIMITIVE_TAG_HPP
