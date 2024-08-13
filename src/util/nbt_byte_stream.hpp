#ifndef CPP_ANVIL_IO_NBT_BYTE_STREAM_HPP
#define CPP_ANVIL_IO_NBT_BYTE_STREAM_HPP

// cpp-anvil
#include <cpp-anvil/nbt.hpp>
#include <cpp-anvil/nbt/types.hpp>

#include "util/byte_swap.hpp"

// STL
#include <bit>
#include <concepts>
#include <istream>
#include <string>
#include <vector>

namespace anvil {
namespace io {

class NbtInputByteStream
{
    using char_type     = unsigned char;
    using pointer       = char_type *;
    using const_pointer = const char_type *;
    using size_type     = std::size_t;

    static constexpr auto EndOfStream{static_cast<size_type>(0)};

public:
    explicit NbtInputByteStream(std::vector<char_type> &data)
        : m_buffer(data)
        , m_pos(0)
    { }

    constexpr size_type size() const noexcept {
        return m_buffer.size();
    }
    constexpr size_type availableBytes() const noexcept {
        if(m_pos >= size()) {
            return EndOfStream;
        } else {
            return size() - m_pos;
        }
    }
    constexpr bool isEof() const noexcept {
        return availableBytes() > 0;
    }

    size_type getPosition() const noexcept {
        return m_pos;
    }
    void setPosition(size_type pos) noexcept {
        m_pos = pos;
    }

    // Reading
    template<typename T>
    T read() {
        constexpr size_type width = sizeof(T);
        if(availableBytes() < width) {
            throw std::runtime_error("Unexpected end of stream.");
        }
        T value;
        std::memcpy(&value, &m_buffer[m_pos], width);
        m_pos += width;
        swapEndian(value);
        return value;
    }

    template<>
    TagType read()
    {
        if(availableBytes() > 0) {
            TagType t = static_cast<TagType>(m_buffer[m_pos]);
            m_pos += 1;
            if(t <= TagType::LongArray) {
                return t;
            }
        }
        return TagType::Unknown;
    }

    template<>
    StringType read()
    {
        uint16_t length = read<uint16_t>();
        if(availableBytes() < length) {
            throw std::runtime_error("Unexpected end of stream.");
        }

        StringType name;
        name.resize(length);
        std::memcpy(name.data(), &m_buffer[m_pos], length);
        m_pos += length;

        return name;
    }

    template<typename T>
    requires anvil::detail::StdVector<T>
    T read() {
        T vec;

        int32_t size = read<int32_t>();
        if(availableBytes() < size) {
            throw std::runtime_error("Unexpected end of stream.");
        }
        vec.resize(size);
        for(int32_t i = 0; i < size; ++i) {
            vec[i] = read<typename T::value_type>();
        }
        return vec;
    }

private:
    template<typename T>
    void swapEndian(T &value) {
        if constexpr(std::endian::native == std::endian::little) {
            value = detail::bswap(value);
        }
    }

private:
    std::vector<char_type>  &m_buffer;
    size_type               m_pos;
};

class NbtOutputByteStream
{
    using char_type     = unsigned char;
    using pointer       = char_type *;
    using const_pointer = const char_type *;
    using size_type     = std::size_t;

    static constexpr auto EndOfStream{static_cast<size_type>(0)};

public:
    explicit NbtOutputByteStream(std::vector<char_type> &data)
        : m_buffer(data)
        , m_pos(0)
    { }

    constexpr size_type capacity() const noexcept {
        return m_buffer.size();
    }

    constexpr size_type size() const noexcept {
        return m_pos;
    }

    size_type getPosition() const noexcept {
        return m_pos;
    }
    void setPosition(size_type pos) noexcept {
        m_pos = pos;
    }

    constexpr size_type availableBytes() const noexcept {
        if(m_pos >= capacity()) {
            return EndOfStream;
        } else {
            return capacity() - m_pos;
        }
    }

    void write(TagType tagType) {
        const size_type len = sizeof(TagType);
        if(availableBytes() < len) {
            grow(len);
        }
        m_buffer[m_pos] = static_cast<unsigned char>(tagType);
        m_pos += len;
    }

    void write(const std::string &str) {
        int16_t str_len = static_cast<int16_t>(str.length());
        swapEndian(str_len);

        const size_type data_len = str.length() + sizeof(int16_t);
        if(availableBytes() < data_len) {
            grow(data_len);
        }
        // Copy string length 
        std::memcpy(&m_buffer[m_pos], &str_len, sizeof(int16_t));
        m_pos += sizeof(int16_t);
        // Copy string content
        std::copy(str.begin(), str.end(), &m_buffer[m_pos]);
        m_pos += str.length();
    }

    template<typename T>
    requires std::integral<T>
    void write(T value) {
        const size_type len = sizeof(T);
        if(availableBytes() < len) {
            grow(len);
        }
        swapEndian(value);
        std::memcpy(&m_buffer[m_pos], &value, len);
        m_pos += len;
    }

    template<typename T>
    requires std::floating_point<T>
    void write(T value) {
        const size_type len = sizeof(T);
        if(availableBytes() < len) {
            grow(len);
        }
        swapEndian(value);
        std::memcpy(&m_buffer[m_pos], &value, len);
        m_pos += len;
    }

private:
    size_type calculateGrowth(const size_type newSize) {
        const size_type oldCapacity = m_buffer.capacity();
        const size_type maxSize     = m_buffer.max_size();

        // Geometric growth would overflow
        if(oldCapacity > maxSize - oldCapacity / 2) {
            return maxSize;
        }

        const size_type geometric = oldCapacity + oldCapacity / 2;

        // Geometric growth is not enough => take new size
        if(geometric < newSize) {
            return newSize;
        }

        return geometric;
    }

    void grow(const size_type count) {
        if(count > m_buffer.max_size() - m_buffer.size()) {
            throw std::runtime_error("ByteStream can not grow. Buffer too long.");
        }

        size_type newSize = m_buffer.size() + count;
        size_type newCapycity = calculateGrowth(newSize);
        m_buffer.resize(newCapycity);
    }

    template<typename T>
    void swapEndian(T &value) {
        if constexpr(std::endian::native == std::endian::little) {
            value = detail::bswap(value);
        }
    }

private:
    std::vector<char_type>  &m_buffer;
    size_type               m_pos;
};

} // namespace io
} // namespace anvil

#endif // CPP_ANVIL_IO_NBT_BYTE_STREAM_HPP
