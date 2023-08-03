#pragma once
#include <limits>

namespace Core_Math
{

#if defined(DOUBLE_PRECISION)   
using numeral = double;
constexpr numeral MAX_NUMERAL{ DBL_MAX };
constexpr numeral EPSILON{ DBL_EPSILON };
constexpr numeral PI{ 3.14159265358979323};
#else                                   
using numeral = float;
constexpr auto MAX_NUMERAL {FLT_MAX};
constexpr auto EPSILON {FLT_EPSILON};
//constexpr auto PI{3.14159265358979323f};
#endif

} // namespace Core_Math