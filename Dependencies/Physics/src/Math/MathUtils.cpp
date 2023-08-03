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

Mat4x4 lookAt(Vector3 Peye, Vector3 Pref, Vector3 up) {
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