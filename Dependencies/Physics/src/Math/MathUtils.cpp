#include "../../include/Math/MathUtils.h"

namespace Core_Math
{
Mat4x4 Ortho(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	Mat4x4 result = Mat4x4::GetIdentity();

	result[0][0] = 2.0f / (right - left);
	result[1][1] = 2.0f / (top - bottom);
	result[2][2] = -2.0f / (far - near);

	result[3][0] = -(right + left) / (right - left);
	result[3][1] = -(top + bottom) / (top - bottom);
	result[3][2] = -(far + near) / (far - near);

	return result;
}
}