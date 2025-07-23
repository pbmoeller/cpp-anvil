#ifndef CPP_ANVIL_NBT_DETAIL_FLOATING_POINT_HPP
#define CPP_ANVIL_NBT_DETAIL_FLOATING_POINT_HPP

#include <cmath>
#include <cstdint>

namespace anvil {

// -------------------------------------------------------------------------------------------------
//      FloatingPoint
// -------------------------------------------------------------------------------------------------

namespace detail {

template<size_t size>
struct SizedIntTypes {
    using Int   = void;
    using UInt  = void;
};
template<>
struct SizedIntTypes<4> {
    using Int   = int32_t;
    using UInt  = uint32_t;
};
template<>
struct SizedIntTypes<8> {
    using Int   = int64_t;
    using UInt  = uint64_t;
};

template<typename FloatingPointType>
class FloatingPoint
{
public:
    // Types
    using Bits = SizedIntTypes<sizeof(FloatingPointType)>::UInt;

    // Constants
    static constexpr size_t BitCount = 8 * sizeof(FloatingPointType);
    static constexpr size_t FractionBitCount
        = std::numeric_limits<FloatingPointType>::digits - 1;
    static constexpr size_t ExponentBitCount = BitCount - 1 - FractionBitCount;
    static constexpr Bits SignBitMask = static_cast<Bits>(1) << (BitCount - 1);
    static constexpr Bits FractionBitMask 
        = ~static_cast<Bits>(0) >> (ExponentBitCount + 1);
    static constexpr Bits ExponentBitMask = ~(SignBitMask | FractionBitMask);

    static constexpr uint32_t MaxUlps = 4;

public:
    explicit FloatingPoint(const FloatingPointType& x) { 
        m_u.value = x;
    }

    static FloatingPointType reinterpretBits(const Bits bits) {
        FloatingPoint fp(0);
        fp.m_u.bits = bits;
        return fp.m_u.value;
    }

    static FloatingPointType infinity() { return reinterpretBits(ExponentBitMask); }

    const Bits& bits() const { return m_u.bits; }

    Bits exponentBits() const { return ExponentBitMask & m_u.bits; }

    Bits fractionBits() const { return FractionBitMask & m_u.bits; }

    Bits signBit() const { return SignBitMask & m_u.bits; }

    bool isNan() const {
        return (exponentBits() == ExponentBitMask) && (fractionBits() != 0);
    }

    bool almostEquals(const FloatingPoint& rhs) const {
        // The IEEE standard says that any comparison operation involving
        // a NAN must return false.
        if(isNan() || rhs.isNan()) {
            return false;
        }

        return distanceBetweenSignAndMagnitudeNumbers(m_u.bits, rhs.m_u.bits) <= MaxUlps;
    }

private:
    union FloatingPointUnion {
        FloatingPointType value;
        Bits bits;
    };

    static Bits signAndMagnitudeToBiased(const Bits& sam) {
        if(SignBitMask & sam) {
            return ~sam + 1;            // sam = negative number
        } else {
            return SignBitMask | sam;  // sam = positive number
        }
    }

    static Bits distanceBetweenSignAndMagnitudeNumbers(const Bits& sam1,
                                                       const Bits& sam2) {
        const Bits biased1 = signAndMagnitudeToBiased(sam1);
        const Bits biased2 = signAndMagnitudeToBiased(sam2);
        return (biased1 >= biased2) ? (biased1 - biased2) : (biased2 - biased1);
    }

private:
    FloatingPointUnion m_u;
};

template<typename T>
bool almostEqual(T lhsValue, T rhsValue) {
    const FloatingPoint<T> lhs(lhsValue);
    const FloatingPoint<T> rhs(rhsValue);
    return lhs.almostEquals(rhs);
}

} // namespace detail
} // namespace anvil

#endif // CPP_ANVIL_NBT_DETAIL_FLOATING_POINT_HPP
