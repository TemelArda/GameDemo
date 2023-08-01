#pragma once
#include "Mat4x4.h"

namespace Core_Math
{
Mat4x4 Ortho(const float left, const float right, const float bottom, const float top, const float near, const float far);
} // namespace Core_Math