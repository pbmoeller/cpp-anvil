#ifndef CPP_ANVIL_NBT_TYPES_HPP
#define CPP_ANVIL_NBT_TYPES_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace anvil {

// -------------------------------------------------------------------------------------------------
//      Types
// -------------------------------------------------------------------------------------------------

enum class TagType : unsigned char
{
    End         = 0,
    Byte        = 1,
    Short       = 2,
    Int         = 3,
    Long        = 4,
    Float       = 5,
    Double      = 6,
    ByteArray   = 7,
    String      = 8,
    List        = 9,
    Compound    = 10,
    IntArray    = 11,
    LongArray   = 12,
    Unknown     = 255,
};

class BasicTag;

using NullType      = std::nullptr_t;
using ByteType      = std::int8_t;
using ShortType     = std::int16_t;
using IntType       = std::int32_t;
using LongType      = std::int64_t;
using FloatType     = float;
using DoubleType    = double;
using StringType    = std::string;

template<typename T>
using ContainerType = std::vector<T>;

// -------------------------------------------------------------------------------------------------
//      Traits
// -------------------------------------------------------------------------------------------------

namespace detail {

template<typename T>
struct IsUniquePtr : std::false_type {};
template<typename T>
struct IsUniquePtr<std::unique_ptr<T>> : std::true_type {};
template<typename T>
constexpr bool IsUniquePtr_v = IsUniquePtr<T>::value;

} // namespace detail

// -------------------------------------------------------------------------------------------------
//      Concepts
// -------------------------------------------------------------------------------------------------

namespace detail {

template<typename, template<typename...> typename>
inline constexpr bool isSpecialization = false;
template<template<typename...> typename T, typename... Args>
inline constexpr bool isSpecialization<T<Args...>, T> = true;

template<typename T>
concept StdVector = isSpecialization<T, std::vector>;

template<typename T>
concept IsStringType = std::same_as<T, StringType>;

} // namespace detail

// -------------------------------------------------------------------------------------------------
//      Functions
// -------------------------------------------------------------------------------------------------

//! @brief Checks if tag type is a primitive type.
//! @param type Tag type.
//! @return `true` if tag type is primitive tag, `false` otherwise.
constexpr bool isPrimitiveTag(TagType type)
{
    return type == TagType::Byte
        || type == TagType::Short
        || type == TagType::Int
        || type == TagType::Long
        || type == TagType::Float
        || type == TagType::Double
        || type == TagType::String;
}

//! @brief Checks if tag type is a array type.
//! @param type Tag type.
//! @return `true` if tag type is array tag, `false` otherwise.
constexpr bool isArrayTag(TagType type)
{
    return type == TagType::ByteArray
        || type == TagType::IntArray
        || type == TagType::LongArray;
}

//! @brief Checks if tag type is a container type.
//! @param type Tag type.
//! @return `true` if tag type is container tag, `false` otherwise.
constexpr bool isContainerTag(TagType type)
{
    return type == TagType::List
        || type == TagType::Compound;
}

//! @brief Checks if tag type is a collection type, i.e. array or container.
//! @param type Tag type.
//! @return `true` if tag type is collection tag, `false` otherwise.
constexpr bool isCollectionTag(TagType type)
{
    return isArrayTag(type)
        || isContainerTag(type);
}

//! @brief Checks if the tag type contains a value.
//! @param type Tag type.
//! @return `true` if tag type is contains a value, `false` otherwise.
constexpr bool isValueTag(TagType type)
{
    return type != TagType::End
        && type != TagType::Unknown;
}

//! @brief Checks if the tag type is valid.
//! @param type Tag type.
//! @return `true` if tag type is valid, `false` otherwise.
constexpr bool isValidTag(TagType type)
{
    return type == TagType::End
        || type == TagType::Byte
        || type == TagType::Short
        || type == TagType::Int
        || type == TagType::Long
        || type == TagType::Float
        || type == TagType::Double
        || type == TagType::ByteArray
        || type == TagType::String
        || type == TagType::List
        || type == TagType::Compound
        || type == TagType::IntArray
        || type == TagType::LongArray;
}

//! @brief Returns the name of the tag type.
//! @param type Tag type.
//! @return Name of tag type. 
std::string_view getTagTypeName(TagType type);

//! @brief Returns the name of the tag.
//! @param type Tag type.
//! @return Name of tag.
std::string_view getTagName(TagType type);

} // namespace anvil

#endif // CPP_ANVIL_NBT_TYPES_HPP
