#include "../../include/Math/MathUtils.h"

namespace Core_Math
{
Mat4x4 Ortho(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	Mat4x4 result = Mat4x4::Identity();

	result[0][0] = 2.0f / (right - left);
	result[1][1] = 2.0f / (top - bottom);
	result[2][2] = -2.0f / (far - near);

	result[3][0] = -(right + left) / (right - left);
	result[3][1] = -(top + bottom) / (top - bottom);
	result[3][2] = -(far + near) / (far - near);

	return result;
}


// FoV is in radians
Mat4x4 Perspective(const float FoV, const float aspect, const float near, const float far)
{
	Mat4x4 result = Mat4x4::Identity();

	const float tanHalfFov = tanf(FoV / 2.0f);
	const float range = near - far;

	result[0][0] = 1.0f / (aspect * tanHalfFov);
	result[1][1] = 1.0f / tanHalfFov;
	result[2][2] = (-near - far) / range;
	result[2][3] = 2.0f * far * near / range;
	result[3][2] = 1.0f;
	result[3][3] = 0.0f;

	return result;
}

Mat4x4 lookAt(const Vector3& Peye, const Vector3& Pref, const Vector3& up) {
	Vector3 zaxis = (Peye - Pref).GetNormalized();
	Vector3 xaxis = Vector3::Cross(zaxis, up);
	xaxis.Normalize();
	Vector3 yaxis = Vector3::Cross(zaxis, xaxis);

	const auto eyedotx = Peye.Dot(xaxis);
	const auto eyedoty = Peye.Dot(yaxis);
	const auto eyedotz = Peye.Dot(zaxis);

	return Mat4x4(
		Vector4(xaxis.x, xaxis.y, xaxis.z, -eyedotx),
		Vector4(yaxis.x, yaxis.y, yaxis.z, -eyedoty),
		Vector4(zaxis.x, zaxis.y, zaxis.z, -eyedotz),
		Vector4(0, 0, 0, 1)
	);
}
}