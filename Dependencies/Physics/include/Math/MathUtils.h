#pragma once
#include "Mat4x4.h"
#include "Vector3.h"

namespace Core_Math
{
Mat4x4 Ortho(const float left, const float right, const float bottom, const float top, const float near, const float far);

Mat4x4 lookAt(Vector3 Peye, Vector3 Pref, Vector3 up);

inline float clamp(float min, float max, float value) {
	return (value < min) ? min : (value > max) ? max : value;
}
} // namespace Core_Math