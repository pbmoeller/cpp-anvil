#ifndef CPP_ANVIL_NBT_DETAIL_TYPE_UTILITIES_HPP
#define CPP_ANVIL_NBT_DETAIL_TYPE_UTILITIES_HPP

#include <memory>
#include <string>
#include <vector>

namespace anvil {
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////
// Traits

template<typename T>
struct IsUniquePtr : std::false_type
{ };
template<typename T>
struct IsUniquePtr<std::unique_ptr<T>> : std::true_type
{ };
template<typename T>
constexpr bool IsUniquePtr_v = IsUniquePtr<T>::value;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Concepts

template<typename, template<typename...> typename>
inline constexpr bool isSpecialization = false;
template<template<typename...> typename T, typename... Args>
inline constexpr bool isSpecialization<T<Args...>, T> = true;

template<typename T>
concept StdVector = isSpecialization<T, std::vector>;

template<typename T>
concept IsStringType = std::same_as<T, std::string>;

} // namespace detail
} // namespace anvil

#endif // CPP_ANVIL_NBT_DETAIL_TYPE_UTILITIES_HPP
