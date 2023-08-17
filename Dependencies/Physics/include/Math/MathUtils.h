#pragma once
#include "Mat4x4.h"
#include "Vector3.h"
#include "Transform3D.h"

namespace Core_Math
{
Mat4x4 Ortho(const float left, const float right, const float bottom, const float top, const float near, const float far);

Mat4x4 Perspective(const float FoV, const float aspect, const float near, const float far);

Mat4x4 LookAt(const Vector3& Peye, const Vector3& Pref, const Vector3& up);

Mat4x4 LookAt(Transform3D& t, const Vector3& Pref, const Vector3& up);

inline float clamp(float min, float max, float value) {
	return (value < min) ? min : (value > max) ? max : value;
}
} // namespace Core_Math