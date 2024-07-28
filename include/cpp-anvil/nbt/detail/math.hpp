#ifndef CPP_ANVIL_NBT_DETAIL_MATH_HPP
#define CPP_ANVIL_NBT_DETAIL_MATH_HPP

// STL
#include <cstdint>
#include <cmath>

namespace nbt {

// -------------------------------------------------------------------------------------------------
//      Math
// -------------------------------------------------------------------------------------------------

namespace detail {

template<typename T>
struct IntSelector {
    using IntType = void;
};
template<>
struct IntSelector<float> {
    using IntType = int32_t;
};
template<>
struct IntSelector<double> {
    using IntType = int64_t;
};

template<typename T, typename IntType = typename IntSelector<T>::IntType>
inline bool almostEqualUlps(T a, T b, IntType maxUlps)
{
    if(std::isinf(a) || std::isinf(b)) {
        return a == b;
    }
    if(std::isnan(a) || std::isnan(b)) {
        return false;
    }
    if(std::signbit(a) != std::signbit(b)) {
        return a == b;
    }

    IntType aInt = *(reinterpret_cast<IntType *>(&a));
    if(aInt < 0) {
        aInt = 0x80000000 - aInt;
    }
    IntType bInt = *(reinterpret_cast<IntType *>(&b));
    if(bInt < 0) {
        bInt = 0x80000000 - bInt;
    }

    IntType diff = std::abs(aInt - bInt);
    if(diff < maxUlps) {
        return true;
    }
    return false;
}

} // namespace detail
} // namespace nbt

#endif // CPP_ANVIL_NBT_DETAIL_MATH_HPP
