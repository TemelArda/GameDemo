#include "../../include/Math/Vector3.h"


namespace Core_Math
{

void Vector3::Normalize()
{
	const auto magnitude = Magnitude();
	if (magnitude > EPSILON)
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
}

Vector3 Vector3::GetNormalized() const
{
	const auto magnitude = Magnitude();
	if (magnitude > EPSILON)
		return Vector3(x /magnitude ,y / magnitude, z / magnitude);
	return Vector3();
	
}

Vector3 Vector3::Cross(const Vector3& vector) const
{
	return Vector3(y * vector.z - z * vector.y,
		z * vector.x - x * vector.z,
		x * vector.y - y * vector.x);
}

bool Vector3::IsZero() const
{
	const auto magnitude = MagnitudeSquared();
	return magnitude <= EPSILON;
}

bool Vector3::IsNormalized() const
{
	const auto magnitude = MagnitudeSquared();
	return abs(magnitude - 1.0) <= EPSILON;
}

Vector3 operator+(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}

Vector3 operator-(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
}

Vector3 operator-(const Vector3& vector)
{
	return Vector3(-vector.x, -vector.y, -vector.z);
}

Vector3 operator*(const Vector3& vector, numeral number)
{
	
	return Vector3(vector.x * number, vector.y * number, vector.z * number);
}

Vector3 operator*(numeral number, const Vector3& vector)
{
	return Vector3(vector.x * number, vector.y * number, vector.z * number);
}

Vector3 operator*(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z);
}

Vector3 operator/(const Vector3& vector, numeral number)
{
	if (abs(number) <= EPSILON )
		return Vector3();
	return Vector3(vector.x / number, vector.y / number, vector.z / number);
}

Vector3 operator/(const Vector3& vector1, const Vector3& vector2)
{
	if (abs(vector2.x) <= EPSILON || abs(vector2.y) <= EPSILON || abs(vector2.z) <= EPSILON)
		return Vector3();
	return Vector3(vector1.x / vector2.x, vector1.y / vector2.y, vector1.z / vector2.z);
}

Vector3 Vector3::Cross(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(vector1.y * vector2.z - vector1.z * vector2.y,
		vector1.z * vector2.x - vector1.x * vector2.z,
		vector1.x * vector2.y - vector1.y * vector2.x);
}
} // namespace Core_Math
