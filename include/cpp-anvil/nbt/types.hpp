#ifndef CPP_ANVIL_NBT_TYPES_HPP
#define CPP_ANVIL_NBT_TYPES_HPP

#include <string>
#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

namespace nbt {

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

constexpr bool isArrayTag(TagType type)
{
    return type == TagType::ByteArray
        || type == TagType::IntArray
        || type == TagType::LongArray;
}

constexpr bool isContainerTag(TagType type)
{
    return type == TagType::List
        || type == TagType::Compound;
}

constexpr bool isCollectionTag(TagType type)
{
    return isArrayTag(type)
        || isContainerTag(type);
}

constexpr bool isValueTag(TagType type)
{
    return type != TagType::End
        && type != TagType::Unknown;
}

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

std::string_view getTagTypeName(TagType type);
std::string_view getTagName(TagType type);

} // namespace nbt

#endif // CPP_ANVIL_NBT_TYPES_HPP
