#pragma once
#include <limits>

namespace Core_Math
{
#if defined(DOUBLE_PRECISION)   
using numeral = double;
#else                                   
using numeral = float;
#endif

const numeral EPSILON = std::numeric_limits<numeral>::epsilon();
const numeral MAX_NUMERAL = std::numeric_limits<numeral>::max();
}