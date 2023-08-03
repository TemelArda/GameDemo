#include "../../include/Math/Quaternion.h"

namespace Core_Math
{
const std::tuple<numeral, const Vector3&> Quaternion::toAxisAngle() const
{
	const auto& normalized = this->GetNormilized();
	numeral angle = 2.0f * acos(normalized.w);
#if defined(DOUBLE_PRECISION)   
	numeral s = sqrt(1.0 - normalized.w * normalized.w);
#else
	numeral s = sqrtf(1.0f - normalized.w * normalized.w);
#endif // 


	if (s < 0.001f)
	{
		return {angle, {1, 0, 0}};
	}
	else
	{
		return {angle, {normalized.x / s, normalized.y / s, normalized.z / s}};
	}
}

const Vector3& Quaternion::toEuler() const
{
	Vector3 angles;
	const auto& q = this->GetNormilized();

	// roll (x-axis rotation)
	numeral sinr_cosp = 2.0f * (q.w * q.x + q.y * q.z);
	numeral cosr_cosp = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
	angles.x = atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
#if defined(DOUBLE_PRECISION)   
	numeral sinp = sqrt(1.0 + 2.0 * (q.w * q.y - q.x * q.z));
	numeral cosp = sqrt(1.0 - 2.0 * (q.w * q.y - q.x * q.z));
#else
	numeral sinp = sqrtf(1.0f + 2.0f * (q.w * q.y - q.x * q.z));
	numeral cosp = sqrtf(1.0f - 2.0f * (q.w * q.y - q.x * q.z));
#endif // 
	angles.y = 2 * atan2(sinp, cosp) - 3.14159265358979323f / 2;

	// yaw (z-axis rotation)
	numeral siny_cosp = 2.0f * (q.w * q.z + q.x * q.y);
	numeral cosy_cosp = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
	angles.z = atan2(siny_cosp, cosy_cosp);

	return angles;
}

const Mat4x4& Quaternion::toMatrix() const
{
	const auto& q = this->GetNormilized();
	//First row of the rotation matatrix
	numeral r00 = 2 * (q.x * q.x + q.y * q.y) - 1;
	numeral r01 = 2 * (q.y * q.z - q.x * q.w);
	numeral r02 = 2 * (q.y * q.w + q.x * q.z);

	//Second row of the rotation matatrix
	numeral r10 = 2 * (q.y * q.z + q.x * q.w);
	numeral r11 = 2 * (q.x * q.x + q.z * q.z) - 1;
	numeral r12 = 2 * (q.z * q.w - q.x * q.y);
	
	//Third row of the rotation matatrix
	numeral r20 = 2 * (q.y * q.w - q.x * q.z);
	numeral r21 = 2 * (q.z * q.w + q.x * q.y);
	numeral r22 = 2 * (q.x * q.x + q.w * q.w) - 1;
	//3x3 rotation matatrix
	return Mat4x4(
		{r00, r01, r02, 0},
		{r10, r11, r12, 0},
		{r20, r21, r22, 0},
		{0, 0, 0, 1});
}

Quaternion Quaternion::FromEuler(const Vector3& euler)
{
	double cr = cos(euler.x * 0.5);
	double sr = sin(euler.x * 0.5);
	double cp = cos(euler.y * 0.5);
	double sp = sin(euler.y * 0.5);
	double cy = cos(euler.z * 0.5);
	double sy = sin(euler.z * 0.5);

	Quaternion q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;

	return q;
}

Quaternion Quaternion::FromEuler(numeral roll, numeral pitch, numeral yaw)
{
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);

	Quaternion q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;

	return q;
}

Quaternion Quaternion::FromAxisAngle(const Vector3& axis, numeral angle)
{
	Quaternion q;
	double s = sin(angle / 2);
	q.x = axis.x * s;
	q.y = axis.y * s;
	q.z = axis.z * s;
	q.w = cos(angle / 2);
	return q;
}

Quaternion Quaternion::FromMatrix(const Mat4x4& mat)
{
	float tr = mat[0][0] + mat[1][1] + mat[2][2];
	Quaternion q;
		if (tr > 0) {
			float S = sqrt(tr + 1.0) * 2; // S=4*qw 
			q.w = 0.25 * S;
			q.x = (mat[2][1] - mat[1][2]) / S;
			q.y = (mat[0][2] - mat[2][0]) / S;
			q.z = (mat[1][0] - mat[0][1]) / S;
		}
		else if ((mat[0][0] > mat[1][1]) && (mat[0][0] > mat[2][2])) {
			float S = sqrt(1.0 + mat[0][0] - mat[1][1] - mat[2][2]) * 2; // S=4*qx 
			q.w = (mat[2][1] - mat[1][2]) / S;
			q.x = 0.25 * S;
			q.y = (mat[0][1] + mat[1][0]) / S;
			q.z = (mat[0][2] + mat[2][0]) / S;
		}
		else if (mat[1][1] > mat[2][2]) {
			float S = sqrt(1.0 + mat[1][1] - mat[0][0] - mat[2][2]) * 2; // S=4*qy
			q.w = (mat[0][2] - mat[2][0]) / S;
			q.x = (mat[0][1] + mat[1][0]) / S;
			q.y = 0.25 * S;
			q.z = (mat[1][2] + mat[2][1]) / S;
		}
		else {
			float S = sqrt(1.0 + mat[2][2] - mat[0][0] - mat[1][1]) * 2; // S=4*qz
			q.w = (mat[1][0] - mat[0][1]) / S;
			q.x = (mat[0][2] - mat[2][0]) / S;
			q.y = (mat[1][2] + mat[2][1]) / S;
			q.z = 0.25 * S;
		}
		return q;
}

Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, numeral t)
{
	return Quaternion();
}

Quaternion Quaternion::Lerp(const Quaternion& q1, const Quaternion& q2, numeral t)
{
	return Quaternion();
}
}

