#ifndef CPP_ANVIL_NBT_BASIC_TAG_HPP
#define CPP_ANVIL_NBT_BASIC_TAG_HPP

#include "cpp-anvil/nbt/types.hpp"

#include <memory>
#include <type_traits>
#include <typeinfo>

namespace anvil {

template<typename T, TagType TAG>
class PrimitiveTag;

template<typename T, TagType TAG>
class CollectionTag;

class EndTag;
class ListTag;
class CompoundTag;

template<typename T>
inline T tag_cast(const BasicTag* item);

class BasicTag
{
public:
    enum
    {
        Type = static_cast<int>(TagType::Unknown)
    };

public:
    //! @brief Constructs basic tag.
    BasicTag() = default;

    //! @brief Copy constructs basic tag.
    //! @param other Other tag.
    BasicTag(const BasicTag& other) = default;

    //! @brief Move constructs basic tag.
    //! @param other Other tag.
    BasicTag(BasicTag&& other) noexcept = default;

    //! @brief Constructs basic tag with name.
    //! @param name Name to be set.
    explicit BasicTag(const StringType& name)
        : m_name(name) { };

    //! @brief Constructs basic tag with name. Moves given aprameter.
    //! @param name NName to be set.
    explicit BasicTag(StringType&& name) noexcept
        : m_name(std::move(name)) { };

    //! @brief Destroys basic tag.
    virtual ~BasicTag() = default;

    //! @brief Assigns @p other basic tag to this tag.
    //! @param other Other tag to be assigned.
    //! @return Returns reference to this tag.
    BasicTag& operator=(const BasicTag& other) = default;

    //! @brief Move assigns @p other basic tag to this tag.
    //! @param other Other tag to be moved.
    //! @return Returns reference to this tag.
    BasicTag& operator=(BasicTag&& other) noexcept = default;

    //! @brief Returns type of this tag.
    //! @details
    //! The type is used for distinguishing between tags and used for by tag_cast.
    //!
    //! @return Tag type.
    constexpr virtual TagType type() const { return TagType::Unknown; }

    //! @brief Returns a copy of this tag.
    //! @return A unique_ptr to copy of this tag.
    virtual std::unique_ptr<BasicTag> clone() const = 0;

    //! @brief Returns name of this tag.
    //! @return Tag name.
    StringType name() { return m_name; }

    //! @brief Returns constant reference to name of this tag.
    //! @return Tag name.
    const StringType& name() const { return m_name; }

    //! @brief Assigns a new name to the tag.
    //! @param name New string to be assigned.
    void setName(const StringType& name) { m_name = name; }

    //! @brief Checks if this tag is an End tag.
    //! @return `true` if checked tag is an End tag, `false` otherwise.
    constexpr bool isEndTag() const { return type() == TagType::End; }

    //! @brief Checks if this tag is a Byte tag.
    //! @return `true` if checked tag is a Byte tag, `false` otherwise.
    constexpr bool isByteTag() const { return type() == TagType::Byte; }

    //! @brief Checks if this tag is a Short tag.
    //! @return `true` if checked tag is a Short tag, `false` otherwise.
    constexpr bool isShortTag() const { return type() == TagType::Short; }

    //! @brief Checks if this tag is an Int tag.
    //! @return `true` if checked tag is an Int tag, `false` otherwise.
    constexpr bool isIntTag() const { return type() == TagType::Int; }

    //! @brief Checks if this tag is a Long tag.
    //! @return `true` if checked tag is a Long tag, `false` otherwise.
    constexpr bool isLongTag() const { return type() == TagType::Long; }

    //! @brief Checks if this tag is a Float tag.
    //! @return `true` if checked tag is a Float tag, `false` otherwise.
    constexpr bool isFloatTag() const { return type() == TagType::Float; }

    //! @brief Checks if this tag is a Double tag.
    //! @return `true` if checked tag is a Double tag, `false` otherwise.
    constexpr bool isDoubleTag() const { return type() == TagType::Double; }

    //! @brief Checks if this tag is a ByteArray tag.
    //! @return `true` if checked tag is a ByteArray tag, `false` otherwise.
    constexpr bool isByteArrayTag() const { return type() == TagType::ByteArray; }

    //! @brief Checks if this tag is a String tag.
    //! @return `true` if checked tag is a String tag, `false` otherwise.
    constexpr bool isStringTag() const { return type() == TagType::String; }

    //! @brief Checks if this tag is a List tag.
    //! @return `true` if checked tag is a List tag, `false` otherwise.
    constexpr bool isListTag() const { return type() == TagType::List; }

    //! @brief Checks if the Tag is a Compound tag.
    //! @return `true` if checked tag is a Compound tag, `false` otherwise.
    constexpr bool isCompoundTag() const { return type() == TagType::Compound; }

    //! @brief Checks if the Tag is an IntArray.
    //! @return `true` if checked tag is an IntArray, `false` otherwise.
    constexpr bool isIntArrayTag() const { return type() == TagType::IntArray; }

    //! @brief Checks if the Tag is a LongArray.
    //! @return `true` if checked tag is a LongArray, `false` otherwise.
    constexpr bool isLongArrayTag() const { return type() == TagType::LongArray; }

    //! @brief Converts the current object to an EndTag pointer if possible.
    //! @return A pointer to an EndTag if the conversion is valid; otherwise, returns `nullptr`.
    EndTag* asEndTag();

    //! @brief Converts the current object to a ByteTag pointer if possible.
    //! @return A pointer to a ByteTag if the conversion is valid; otherwise, returns `nullptr`.
    PrimitiveTag<ByteType, TagType::Byte>* asByteTag();

    //! @brief Converts the current object to a ShortTag pointer if possible.
    //! @return A pointer to a ShortTag if the conversion is valid; otherwise, returns `nullptr`.
    PrimitiveTag<ShortType, TagType::Short>* asShortTag();

    //! @brief Converts the current object to an IntTag pointer if possible.
    //! @return A pointer to an IntTag if the conversion is valid; otherwise, returns `nullptr`.
    PrimitiveTag<IntType, TagType::Int>* asIntTag();

    //! @brief Converts the current object to a LongTag pointer if possible.
    //! @return A pointer to a LongTag if the conversion is valid; otherwise, returns `nullptr`.
    PrimitiveTag<LongType, TagType::Long>* asLongTag();

    //! @brief Converts the current object to a FloatTag pointer if possible.
    //! @return A pointer to a FloatTag if the conversion is valid; otherwise, returns `nullptr`.
    PrimitiveTag<FloatType, TagType::Float>* asFloatTag();

    //! @brief Converts the current object to a DoubleTag pointer if possible.
    //! @return A pointer to a DoubleTag if the conversion is valid; otherwise, returns `nullptr`.
    PrimitiveTag<DoubleType, TagType::Double>* asDoubleTag();

    //! @brief Converts the current object to a ByteArrayTag pointer if possible.
    //! @return A pointer to a ByteArrayTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    CollectionTag<ByteType, TagType::ByteArray>* asByteArrayTag();

    //! @brief Converts the current object to a StringTag pointer if possible.
    //! @return A pointer to a StringTag if the conversion is valid; otherwise, returns `nullptr`.
    PrimitiveTag<StringType, TagType::String>* asStringTag();

    //! @brief Converts the current object to a IntArrayTag pointer if possible.
    //! @return A pointer to a IntArrayTag if the conversion is valid; otherwise, returns `nullptr`.
    CollectionTag<IntType, TagType::IntArray>* asIntArrayTag();

    //! @brief Converts the current object to a LongArrayTag pointer if possible.
    //! @return A pointer to a LongArrayTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    CollectionTag<LongType, TagType::LongArray>* asLongArrayTag();

    //! @brief Converts the current object to a ListTag pointer if possible.
    //! @return A pointer to a ListTag if the conversion is valid; otherwise, returns `nullptr`.
    ListTag* asListTag();

    //! @brief Converts the current object to a CompoundTag pointer if possible.
    //! @return A pointer to a CompoundTag if the conversion is valid; otherwise, returns `nullptr`.
    CompoundTag* asCompoundTag();

    //! @brief Converts the current object to an const EndTag pointer if possible.
    //! @return A const pointer to an EndTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const EndTag* asEndTag() const;

    //! @brief Converts the current object to a const ByteTag pointer if possible.
    //! @return A const pointer to a ByteTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const PrimitiveTag<ByteType, TagType::Byte>* asByteTag() const;

    //! @brief Converts the current object to a const ShortTag pointer if possible.
    //! @return A const pointer to a ShortTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const PrimitiveTag<ShortType, TagType::Short>* asShortTag() const;

    //! @brief Converts the current object to an const IntTag pointer if possible.
    //! @return A const pointer to an IntTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const PrimitiveTag<IntType, TagType::Int>* asIntTag() const;

    //! @brief Converts the current object to a const LongTag pointer if possible.
    //! @return A const pointer to a LongTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const PrimitiveTag<LongType, TagType::Long>* asLongTag() const;

    //! @brief Converts the current object to a const FloatTag pointer if possible.
    //! @return A const pointer to a FloatTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const PrimitiveTag<FloatType, TagType::Float>* asFloatTag() const;

    //! @brief Converts the current object to a const DoubleTag pointer if possible.
    //! @return A const pointer to a DoubleTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const PrimitiveTag<DoubleType, TagType::Double>* asDoubleTag() const;

    //! @brief Converts the current object to a const ByteArrayTag pointer if possible.
    //! @return A const pointer to a ByteArrayTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const CollectionTag<ByteType, TagType::ByteArray>* asByteArrayTag() const;

    //! @brief Converts the current object to a const StringTag pointer if possible.
    //! @return A const pointer to a StringTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const PrimitiveTag<StringType, TagType::String>* asStringTag() const;

    //! @brief Converts the current object to a const IntArrayTag pointer if possible.
    //! @return A const pointer to a IntArrayTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const CollectionTag<IntType, TagType::IntArray>* asIntArrayTag() const;

    //! @brief Converts the current object to a const LongArrayTag pointer if possible.
    //! @return A const pointer to a LongArrayTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const CollectionTag<LongType, TagType::LongArray>* asLongArrayTag() const;

    //! @brief Converts the current object to a const ListTag pointer if possible.
    //! @return A const pointer to a ListTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const ListTag* asListTag() const;

    //! @brief Converts the current object to a const CompoundTag pointer if possible.
    //! @return A const pointer to a CompoundTag if the conversion is valid; otherwise, returns
    //! `nullptr`.
    const CompoundTag* asCompoundTag() const;

    //! @brief Casts the current object to a pointer of the specified type using tag_cast.
    //! @tparam T The type to cast the current object to.
    //! @return A pointer to the current object cast to type T*.
    template<typename T>
    T* as()
    {
        return tag_cast<T*>(this);
    }

    //! @brief Casts the current object to a const pointer of the specified type using tag_cast.
    //! @tparam T The type to cast the current object to.
    //! @return A const pointer to the current object, cast to const T*.
    template<typename T>
    const T* as() const
    {
        return tag_cast<const T*>(this);
    }

protected:
    //! @brief Compares this tag with an other tag for equality.
    //! @param other Other tag to be compared with.
    //! @return `true` if both tags are equal, `false` otherwise.
    virtual bool isEqual(const BasicTag& other) const
    {
        if(this == &other) {
            return true;
        }
        return type() == other.type() && m_name == other.m_name;
    }

    //! \brief Compares two tags with each other for equality.
    //! @param lhs First tag to compare.
    //! @param rhs Second tag to compare.
    //! @return Returns `true` if @p lhs is equal to @p rhs.
    friend bool operator==(const BasicTag& lhs, const BasicTag& rhs)
    {
        return &lhs == &rhs || (typeid(lhs) == typeid(rhs) && lhs.isEqual(rhs));
    }

    //! @brief Compares two tags with each other for inequality.
    //! @param lhs First tag to compare.
    //! @param rhs Second tag to compare.
    //! @return Returns `true` if @p lhs is not equal to @p rhs.
    friend bool operator!=(const BasicTag& lhs, const BasicTag& rhs) { return !(lhs == rhs); }

private:
    StringType m_name;
};

//! @brief Casts a basic tag pointer into a derived basic tag type.
//! @details
//! The cast checks if the type of the basic tag allows a static_cast into the target type.
//! If the target type does not match the item type a `nullptr` is returned.
//!
//! @tparam T   The target type for the cast.
//! @param item Pointer to basic tag to be cast.
//! @return Returns the given tag cast to type @p T if the object is of type T, otherwise returns
//!         `nullptr`.
template<typename T>
inline T tag_cast(BasicTag* item)
{
    using Item = typename std::remove_cv_t<typename std::remove_pointer_t<T>>;
    return int(Item::Type) == int(BasicTag::Type) || (item && int(Item::Type) == int(item->type()))
             ? static_cast<T>(item)
             : nullptr;
}

//! @brief Casts a const basic tag pointer into a derived basic tag type.
//! @details
//! The cast checks if the type of the basic tag allows a static_cast into the target type.
//! If the target type does not match the item type a `nullptr` is returned.
//!
//! @tparam T   The target type for the cast.
//! @param item Pointer to basic tag to be cast.
//! @return Returns the given tag cast to type @p T if the object is of type T, otherwise returns
//!         `nullptr`.
template<typename T>
inline T tag_cast(const BasicTag* item)
{
    using Item = typename std::remove_cv_t<typename std::remove_pointer_t<T>>;
    return int(Item::Type) == int(BasicTag::Type) || (item && int(Item::Type) == int(item->type()))
             ? static_cast<T>(item)
             : nullptr;
}

//! @brief Casts a basic tag which is embedded in a unique_ptr into a derived basic tag type
//!        embedded in a unique_ptr.
//! @details
//! The cast checks if the type of the basic tag allows a static_cast into the target type.
//! If the target type does not match the item type a `nullptr` is returned.
//!
//! When the basic tag can be converted the existing unqiue_ptr will be released and wrapped
//! into a new unqiue_ptr.
//!
//! @tparam T The target type for the cast.
//! @param item Pointer to basic tag to be cast.
//! @return Returns the given tag cast to type @p T if the object is of type T, otherwise returns
//!         `nullptr`.
template<typename T>
inline std::unique_ptr<T> tag_cast(std::unique_ptr<BasicTag>&& item)
{
    using Item = typename std::remove_cv_t<typename std::remove_pointer_t<T>>;
    if(int(T::Type) == int(Item::Type) || (item && int(T::Type) == int(item->type()))) {
        T* t = static_cast<T*>(item.release());
        return std::unique_ptr<T>(t);
    }
    return nullptr;
}

class EndTag : public BasicTag
{
public:
    enum
    {
        Type = static_cast<int>(TagType::End)
    };

public:
    //! @brief Returns tag type.
    //! @return TagType::End.
    constexpr virtual TagType type() const override { return TagType::End; }

    //! @brief Returns a copy of this tag. Reimplements clone function from BasicTag.
    //! @return A unique_ptr to copy of this tag.
    virtual std::unique_ptr<BasicTag> clone() const override
    {
        return std::make_unique<EndTag>(*this);
    }

    //! @brief Compares this tag with an other tag for equality.
    //! @param other Other tag to be compared with.
    //! @return `true` if both tags are equal, `false` otherwise.
    virtual bool isEqual(const BasicTag& other) const override
    {
        if(this == &other) {
            return true;
        }
        return type() == other.type();
    }
};

} // namespace anvil

#endif // CPP_ANVIL_NBT_BASIC_TAG_HPP
