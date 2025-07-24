#ifndef CPP_ANVIL_NBT_BASIC_TAG_HPP
#define CPP_ANVIL_NBT_BASIC_TAG_HPP

#include "cpp-anvil/nbt/types.hpp"

#include <memory>
#include <type_traits>
#include <typeinfo>

namespace anvil {

class BasicTag
{
public:
    enum { Type = static_cast<int>(TagType::Unknown) };

public:
    //! @brief Constructs basic tag.
    BasicTag() = default;

    //! @brief Copy constructs basic tag.
    //! @param other Other tag.
    BasicTag(const BasicTag &other) = default;
    
    //! @brief Move constructs basic tag.
    //! @param other Other tag.
    BasicTag(BasicTag &&other) noexcept = default;

    //! @brief Constructs basic tag with name.
    //! @param name Name to be set.
    explicit BasicTag(const StringType &name)
        : m_name(name) {};

    //! @brief Constructs basic tag with name. Moves given aprameter.
    //! @param name NName to be set.
    explicit BasicTag(StringType &&name) noexcept
        : m_name(std::move(name)) {};

    //! @brief Destroys basic tag.
    virtual ~BasicTag() = default;

    //! @brief Assigns @p other basic tag to this tag.
    //! @param other Other tag to be assigned.
    //! @return Returns reference to this tag.
    BasicTag& operator=(const BasicTag &other) = default;

    //! @brief Move assigns @p other basic tag to this tag.
    //! @param other Other tag to be moved.
    //! @return Returns reference to this tag.
    BasicTag& operator=(BasicTag &&other) noexcept = default;

    //! @brief Returns type of this tag.
    //! @details
    //! The type is used for distinguishing between tags and used for by tag_cast.
    //! 
    //! @return Tag type.
    constexpr virtual TagType type() const {
        return TagType::Unknown;
    }

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
    void setName(const StringType &name) { m_name = name; }

protected:
    //! @brief Compares this tag with an other tag for equality.
    //! @param other Other tag to be compared with.
    //! @return `true` if both tags are equal, `false` otherwise.
    virtual bool isEqual(const BasicTag &other) const {
        if(this == &other) {
            return true;
        }
        return type() == other.type()
            && m_name == other.m_name;
    }

    //! \brief Compares two tags with each other for equality.
    //! @param lhs First tag to compare.
    //! @param rhs Second tag to compare.
    //! @return Returns `true` if @p lhs is equal to @p rhs.
    friend bool operator==(const BasicTag &lhs, const BasicTag &rhs) {
        return &lhs == &rhs
            || (typeid(lhs) == typeid(rhs) && lhs.isEqual(rhs));
    }

    //! @brief Compares two tags with each other for inequality.
    //! @param lhs First tag to compare.
    //! @param rhs Second tag to compare.
    //! @return Returns `true` if @p lhs is not equal to @p rhs. 
    friend bool operator!=(const BasicTag &lhs,
                           const BasicTag &rhs) {
        return !(lhs == rhs);
    }

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
inline T tag_cast(BasicTag *item)
{
    typedef typename std::remove_cv<typename std::remove_pointer<T>::type>::type Item;
    return int(Item::Type) == int(BasicTag::Type)
        || (item && int(Item::Type) == int(item->type())) ? static_cast<T>(item) : nullptr;
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
inline T tag_cast(const BasicTag *item)
{
    typedef typename std::remove_cv<typename std::remove_pointer<T>::type>::type Item;
    return int(Item::Type) == int(BasicTag::Type)
        || (item && int(Item::Type) == int(item->type())) ? static_cast<T>(item) : nullptr;
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

class EndTag : public BasicTag
{
public:
    enum { Type = static_cast<int>(TagType::End) };

public:
    //! @brief Returns tag type.
    //! 
    //! @return TagType::End.
    constexpr virtual TagType type() const override {
        return TagType::End;
    }

    //! @brief Returns a copy of this tag. Reimplements clone function from BasicTag.
    //! 
    //! @return A unique_ptr to copy of this tag.
    virtual std::unique_ptr<BasicTag> clone() const override {
        return std::make_unique<EndTag>(*this);
    }

    //! @brief Compares this tag with an other tag for equality.
    //! 
    //! @param other Other tag to be compared with.
    //! 
    //! @return `true` if both tags are equal, `false` otherwise.
    virtual bool isEqual(const BasicTag &other) const override {
        if(this == &other) {
            return true;
        }
        return type() == other.type();
    }
};

} // namespace anvil

#endif // CPP_ANVIL_NBT_BASIC_TAG_HPP
