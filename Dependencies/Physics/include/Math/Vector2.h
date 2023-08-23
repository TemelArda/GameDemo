#pragma once
#include "MathCommon.h"
#include <initializer_list>
#include <math.h>
#include <assert.h>
#include <utility>

namespace Core_Math
{

enum Direction
{
	Clockwise = 1,
	CounterClockwise = -1
};

class Vector2
{
public:
	numeral x;

	numeral y;

public:

	Vector2() noexcept;

	Vector2(numeral value) noexcept;

	Vector2(numeral x, numeral y) noexcept;

	~Vector2() = default;

	Vector2(const Vector2& vector) noexcept;

	Vector2(Vector2&& vector) noexcept :
		x(std::move(vector.x)),
		y(std::move(vector.y))
	{
	}

	Vector2& operator=(const Vector2& vector) noexcept = default;

	void operator=(const std::initializer_list<numeral>& values);

	Vector2& operator=(Vector2&& vector) noexcept = default;

	void SetVector2(numeral x, numeral y) noexcept;

	void SetToZero() noexcept;

	const numeral Magnitude() const;

	const numeral MagnitudeSquared() const;

	void Normalize();

	Vector2 GetNormalized() const;

	numeral Dot(const Vector2& vector) const;
	
	Vector2 PerpendicularVector(const Vector2& vector2, Direction dir) const;

	bool IsZero() const;

	bool IsNormalized() const;

	bool IsFinite() const;

	bool operator==(const Vector2& vector) const;

	bool operator!=(const Vector2& vector) const;

	void operator+=(const Vector2& vector);

	void operator-=(const Vector2& vector);

	void operator*=(const Vector2& vector);

	void operator*=(numeral value);

	void operator/=(const Vector2& vector);

	void operator/=(numeral value);

	const numeral operator[](int index) const;

	numeral& operator[](int index);

	// -------------------- Friends -------------------- //

	friend Vector2 operator+(const Vector2& vector1, const Vector2& vector2);
	friend Vector2 operator-(const Vector2& vector1, const Vector2& vector2);
	friend Vector2 operator-(const Vector2& vector);
	friend Vector2 operator*(const Vector2& vector, numeral number);
	friend Vector2 operator*(numeral number, const Vector2& vector);
	friend Vector2 operator*(const Vector2& vector1, const Vector2& vector2);
	friend Vector2 operator/(const Vector2& vector, numeral number);
	friend Vector2 operator/(const Vector2& vector1, const Vector2& vector2);
};

inline Vector2::Vector2() noexcept
	: x(0.0f), y(0.0f)
{
}

inline Vector2::Vector2(numeral value) noexcept
	: x(value), y(value)
{
}

inline Vector2::Vector2(numeral x, numeral y) noexcept
	: x(x), y(y)
{
}

inline Vector2::Vector2(const Vector2& vector) noexcept
	: x(vector.x), y(vector.y)
{
}
inline void Vector2::SetVector2(numeral x, numeral y) noexcept
{
	this->x = x;
	this->y = y;
}

inline void Vector2::SetToZero() noexcept
{
	x = 0.0f;
	y = 0.0f;
}

inline const numeral Core_Math::Vector2::Magnitude() const
{
	return sqrtf(x * x + y * y);
}

inline const numeral Core_Math::Vector2::MagnitudeSquared() const
{
	return abs(x * x + y * y);
}

inline numeral Vector2::Dot(const Vector2& vector) const
{
	return (x * vector.x + y * vector.y);
}

inline Vector2 Vector2::PerpendicularVector(const Vector2& vector2, Direction dir) const
{
	int sign = (int) dir;
	return Vector2((sign) * vector2.y, (-sign) * vector2.x);
}

inline bool Vector2::IsFinite() const
{
	return isfinite<numeral>(x) && isfinite<numeral>(y);
}

inline void Vector2::operator=(const std::initializer_list<numeral>& values)
{
	if (values.size() != 2)
	{
		return;
	}
	x = *(values.begin());
	y = *(values.begin() + 1);
}

inline bool Vector2::operator==(const Vector2& vector) const
{
	return (x == vector.x && y == vector.y);
}

inline bool Vector2::operator!=(const Vector2& vector) const
{
	return (x != vector.x || y != vector.y);
}

inline void Vector2::operator+=(const Vector2& vector)
{
	x += vector.x;
	y += vector.y;
}

inline void Vector2::operator-=(const Vector2& vector)
{
	x -= vector.x;
	y -= vector.y;
}

inline void Vector2::operator*=(const Vector2& vector)
{
	x *= vector.x;
	y *= vector.y;
}

inline void Vector2::operator/=(numeral value)
{
	if (abs(value) <= EPSILON)
		return;
	x /= value;
	y /= value;
}

inline void Vector2::operator/=(const Vector2& vector)
{
	if (abs(vector.x) <= EPSILON || abs(vector.y) <= EPSILON)
		return;
	x /= vector.x;
	y /= vector.y;
}

inline void Vector2::operator*=(numeral value)
{
	x *= value;
	y *= value;
}

inline const numeral Vector2::operator[](int index) const
{
	if (index > 1)
		assert(false);
	return (&x)[index];
}

inline numeral& Vector2::operator[](int index)
{
	if (index > 1)
	{
		assert(false);
	}
		
	return (&x)[index];
}

}
