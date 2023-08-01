#include "../../include/Math/Vector2.h"


namespace Core_Math
{

void Vector2::Normalize()
{
	const auto magnitude = Magnitude();
	if (magnitude > EPSILON)
	{
		x /= magnitude;
		y /= magnitude;
	}
}

Vector2 Vector2::GetNormalized() const
{
	const auto magnitude = Magnitude();
	if (magnitude > EPSILON)
		return Vector2(x / magnitude, y / magnitude);
	return Vector2();

}

bool Vector2::IsZero() const
{
	const auto magnitude = MagnitudeSquared();
	return magnitude <= EPSILON;
}

bool Vector2::IsNormalized() const
{
	const auto magnitude = MagnitudeSquared();
	return abs(magnitude - 1.0) <= EPSILON;
}

Vector2 operator+(const Vector2& vector1, const Vector2& vector2)
{
	return Vector2(vector1.x + vector2.x, vector1.y + vector2.y);
}

Vector2 operator-(const Vector2& vector1, const Vector2& vector2)
{
	return Vector2(vector1.x - vector2.x, vector1.y - vector2.y);
}

Vector2 operator-(const Vector2& vector)
{
	return Vector2(-vector.x, -vector.y);
}

Vector2 operator*(const Vector2& vector, numeral number)
{

	return Vector2(vector.x * number, vector.y * number);
}

Vector2 operator*(numeral number, const Vector2& vector)
{
	return Vector2(vector.x * number, vector.y * number);
}

Vector2 operator*(const Vector2& vector1, const Vector2& vector2)
{
	return Vector2(vector1.x * vector2.x, vector1.y * vector2.y);
}

Vector2 operator/(const Vector2& vector, numeral number)
{
	if (abs(number) <= EPSILON)
		return Vector2();
	return Vector2(vector.x / number, vector.y / number);
}

Vector2 operator/(const Vector2& vector1, const Vector2& vector2)
{
	if (abs(vector2.x) <= EPSILON || abs(vector2.y) <= EPSILON)
		return Vector2();
	return Vector2(vector1.x / vector2.x, vector1.y / vector2.y);
}

} // namespace Core_Math
