#ifndef CPP_ANVIL_NBT_HPP
#define CPP_ANVIL_NBT_HPP

// cpp-anvil
#include <cpp-anvil/nbt/basic_tag.hpp>
#include <cpp-anvil/nbt/collection_tag.hpp>
#include <cpp-anvil/nbt/compound_tag.hpp>
#include <cpp-anvil/nbt/list_tag.hpp>
#include <cpp-anvil/nbt/primitive_tag.hpp>
#include <cpp-anvil/nbt/types.hpp>

// STL
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <string_view>

namespace nbt_old {

// -------------------------------------------------------------------------------------------------
//      ArrayTag
// -------------------------------------------------------------------------------------------------

// template<typename T, TagType TAG>
// class ArrayTag : public NamedTag
// {
// public:
//     using value_type        = T;
//     using size_type         = typename ContainerType<T>::size_type;
//     using difference_type   = typename ContainerType<T>::difference_type;
//     using pointer           = typename ContainerType<T>::pointer;
//     using const_pointer     = typename ContainerType<T>::const_pointer;
//     using reference         = T&;
//     using const_reference   = const T&;
// 
//     using iterator          = typename ContainerType<T>::iterator;
//     using const_iterator    = typename ContainerType<T>::const_iterator;
// 
//     using reverse_iterator          = typename ContainerType<T>::reverse_iterator;
//     using const_reverse_iterator    = typename ContainerType<T>::const_reverse_iterator;
// 
//     enum { Type = static_cast<int>(TAG) };
// 
// public:
//     ArrayTag() = default;
//     ArrayTag(const ArrayTag &other) = default;
//     ArrayTag(ArrayTag &&other) noexcept = default;
//     explicit ArrayTag(const std::string &name)
//         : NamedTag(name) {};
//     explicit ArrayTag(const ContainerType<T> &value)
//         : NamedTag(), m_value(value) {};
//     explicit ArrayTag(const std::string &name, const ContainerType<T> &value) noexcept
//         : NamedTag(name), m_value(value) {};
//     virtual ~ArrayTag() = default;
// 
//     ArrayTag& operator=(const ArrayTag &other) = default;
//     ArrayTag& operator=(ArrayTag &&other) noexcept = default;
// 
//     constexpr virtual TagType type() const { return TAG; }
// 
//     virtual std::unique_ptr<BasicTag> clone() const override {
//         return std::make_unique<ArrayTag<T, TAG>>(*this);
//     }
// 
//     ContainerType<T>& value() { return m_value; }
//     const ContainerType<T>& value() const { return m_value; }
//     void setValue(const ContainerType<T> &value) { m_value = value; }
// 
// //    // Element access
// //    constexpr reference at(size_type pos) { return m_value.at(pos); }
// //    constexpr const_reference at(const size_type pos) const { return m_value.at(pos); }
// //
// //    constexpr reference operator[](size_type pos) { return m_value[pos]; }
// //    constexpr const_reference operator[](size_type pos) const { return m_value[pos]; }
// //
// //    constexpr reference front() { return m_value.front(); }
// //    constexpr const_reference front() const { return m_value.front(); }
// //
// //    constexpr reference back() { return m_value.back(); }
// //    constexpr const_reference back() const { return m_value.back(); }
// //    
// //
// //    // Iterators
// //    constexpr iterator begin() noexcept { return m_value.begin(); }
// //    constexpr const_iterator begin() const noexcept { return m_value.begin(); }
// //    constexpr const_iterator cbegin() const noexcept { return m_value.cbegin(); }
// //
// //    constexpr iterator end() noexcept { return m_value.end(); }
// //    constexpr const_iterator end() const noexcept { return m_value.end(); }
// //    constexpr const_iterator cend() const noexcept { return m_value.cend(); }
// //
// //    constexpr reverse_iterator rbegin() noexcept { return m_value.rbegin(); }
// //    constexpr const_reverse_iterator rbegin() const noexcept { return m_value.rbegin(); }
// //    constexpr const_reverse_iterator crbegin() const noexcept { return m_value.crbegin(); }
// //
// //    constexpr reverse_iterator rend() noexcept { return m_value.rend(); }
// //    constexpr const_reverse_iterator rend() const noexcept { return m_value.rend(); }
// //    constexpr const_reverse_iterator crend() const noexcept { return m_value.crend(); }
// //
// //    // Capacity
// //    constexpr size_type maxSize() const noexcept { m_value.max_size(); }
// //    void reserve(size_type newCapacity) { m_value.reserve(newCapacity); }
// //
// //    // Modifiers
// //    constexpr void clear() { m_value.clear(); }
// //    template<class...Args>
// //    iterator emplace(const_iterator pos, Args&&... args) { m_value.emplace(pos, std::forward<Args>(args)...); }
// //    template<class...Args>
// //    reference emplace_back(Args&&... args) { m_value.emplace_back(std::forward<Args>(args)...); }
// //    constexpr iterator erase(const_iterator pos) { m_value.erase(pos); }
// //    constexpr iterator erase(const_iterator first, const_iterator last) { m_value.erase(first, last); }
// //    constexpr void eraseAt(size_type pos) { m_value.erase(m_value.begin() + pos); }
// //
// //    constexpr iterator insert(const_iterator pos, const T& value) { return m_value.insert(pos, value); }
// //    constexpr iterator insert(const_iterator pos, T&& value) { return m_value.insert(pos, std::move(value)); }
// //    constexpr iterator insert(const_iterator pos, size_type count, const T& value) { 
// //        return m_value.insert(pos, count, value);
// //    }
// //    template<class InputIt>
// //    constexpr iterator insert(const_iterator pos, InputIt first, InputIt last) {
// //        return m_value.insert(pos, first, last);
// //    }
// //    constexpr iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
// //        return m_value.insert(pos, ilist);
// //    }
// //
// //    constexpr void resize(size_type count) { m_value.resize(count); }
// //    constexpr void resize(size_type count, const value_type& value) { m_value.resize(count, value); }
// 
// protected:
//     virtual bool isEqual(const BasicTag &other) const override
//     {
//         const ArrayTag<T, TAG> &otherTag = static_cast<const ArrayTag<T, TAG>&>(other);
// 
//         return type() == otherTag.type()
//             && name() == otherTag.name()
//             && value() == otherTag.value();
//     }
// 
// private:
//     ContainerType<T> m_value{};
// };

} // namespace nbt_old

#endif // CPP_NBT_NBT_HPP
