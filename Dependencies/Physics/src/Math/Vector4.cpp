#include "../../include/Math/Vector4.h"


namespace Core_Math
{

void Vector4::Normalize()
{
	const auto magnitude = Magnitude();
	if (magnitude > EPSILON)
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
	}
}

Vector4 Vector4::GetNormalized() const
{
	const auto magnitude = Magnitude();
	if (magnitude > EPSILON)
		return Vector4(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
	return Vector4();

}

bool Vector4::IsZero() const
{
	const auto magnitude = MagnitudeSquared();
	return magnitude <= EPSILON;
}

bool Vector4::IsNormalized() const
{
	const auto magnitude = MagnitudeSquared();
	return abs(magnitude - 1.0) <= EPSILON;
}

Vector4 operator+(const Vector4& vector1, const Vector4& vector2)
{
	return Vector4(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z, vector1.w + vector2.w);
}

Vector4 operator-(const Vector4& vector1, const Vector4& vector2)
{
	return Vector4(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z, vector1.w - vector2.w);
}

Vector4 operator-(const Vector4& vector)
{
	return Vector4(-vector.x, -vector.y, -vector.z, -vector.w);
}

Vector4 operator*(const Vector4& vector, numeral number)
{

	return Vector4(vector.x * number, vector.y * number, vector.z * number, vector.w * number);
}

Vector4 operator*(numeral number, const Vector4& vector)
{
	return Vector4(vector.x * number, vector.y * number, vector.z * number, vector.w * number);
}

Vector4 operator*(const Vector4& vector1, const Vector4& vector2)
{
	return Vector4(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z, vector1.w * vector2.w);
}

Vector4 operator/(const Vector4& vector, numeral number)
{
	if (abs(number) <= EPSILON)
		return Vector4();
	return Vector4(vector.x / number, vector.y / number, vector.z / number, vector.w / number);
}

Vector4 operator/(const Vector4& vector1, const Vector4& vector2)
{
	if (abs(vector2.x) <= EPSILON || abs(vector2.y) <= EPSILON || abs(vector2.z) <= EPSILON)
		return Vector4();
	return Vector4(vector1.x / vector2.x, vector1.y / vector2.y, vector1.z / vector2.z, vector1.w / vector2.w);
}

} // namespace Core_Math
