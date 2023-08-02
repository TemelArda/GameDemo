#pragma once
#include <limits>

namespace Core_Math
{
#if defined(DOUBLE_PRECISION)   
using numeral = double;
constexpr numeral MAX_NUMERAL{ DBL_MAX };
constexpr numeral EPSILON{ DBL_EPSILON };
#else                                   
using numeral = float;
constexpr numeral MAX_NUMERAL {FLT_MAX};
constexpr numeral EPSILON {FLT_EPSILON};
#endif
} // namespace Core_Math