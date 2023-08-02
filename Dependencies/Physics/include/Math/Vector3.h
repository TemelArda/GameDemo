#pragma once
#include "MathCommon.h"
#include <initializer_list>
#include <math.h>
#include <assert.h>

namespace Core_Math
{

class Vector3
{
public:
	numeral x;

	numeral y;

	numeral z;
public:

	Vector3();

	Vector3(numeral value);

	Vector3(numeral x, numeral y, numeral z);

	~Vector3() = default;

	Vector3(const Vector3& vector);

	void SetVector3(numeral x, numeral y, numeral z);

	void SetToZero();

	const numeral Magnitude() const;

	const numeral MagnitudeSquared() const;

	void Normalize();

	Vector3 GetNormalized() const;

	numeral Dot(const Vector3& vector) const;

	Vector3 Cross(const Vector3& vector) const;

	bool IsZero() const;

	bool IsNormalized() const;

	bool IsFinite() const;

	void operator=(const Vector3& vector);

	void operator=(const std::initializer_list<numeral>& values);

	bool operator==(const Vector3& vector) const;

	bool operator!=(const Vector3& vector) const;

	void operator+=(const Vector3& vector);

	void operator-=(const Vector3& vector);

	void operator*=(const Vector3& vector);

	void operator*=(numeral value);

	void operator/=(const Vector3& vector);

	void operator/=(numeral value);

	const numeral operator[](int index) const;

	numeral& operator[](int index);

	// -------------------- Friends -------------------- //

	friend Vector3 operator+(const Vector3& vector1, const Vector3& vector2);
	friend Vector3 operator-(const Vector3& vector1, const Vector3& vector2);
	friend Vector3 operator-(const Vector3& vector);
	friend Vector3 operator*(const Vector3& vector, numeral number);
	friend Vector3 operator*(numeral number, const Vector3& vector);
	friend Vector3 operator*(const Vector3& vector1, const Vector3& vector2);
	friend Vector3 operator/(const Vector3& vector, numeral number);
	friend Vector3 operator/(const Vector3& vector1, const Vector3& vector2);

	static Vector3 Cross(const Vector3& vector1, const Vector3& vector2);
};

inline Vector3::Vector3()
	: x(0.0f), y(0.0f), z(0.0f)
{
}

inline Vector3::Vector3(numeral value)
	: x(value), y(value), z(value)
{
}

inline Vector3::Vector3(numeral x, numeral y, numeral z)
	: x(x), y(y), z(z)
{
}

inline Vector3::Vector3(const Vector3& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

inline void Vector3::SetVector3(numeral x, numeral y, numeral z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

inline void Vector3::SetToZero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

inline const numeral Core_Math::Vector3::Magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

inline const numeral Core_Math::Vector3::MagnitudeSquared() const
{
	return abs(x * x + y * y + z * z);
}

inline numeral Vector3::Dot(const Vector3& vector) const
{
	return (x * vector.x + y * vector.y + z * vector.z);
}

inline bool Vector3::IsFinite() const
{
	return isfinite<numeral>(x) && isfinite<numeral>(y) && isfinite<numeral>(z);
}

inline void Vector3::operator=(const Vector3& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

inline void Vector3::operator=(const std::initializer_list<numeral>& values)
{
	if (values.size() != 3)
	{
		return;
	}
	x = *(values.begin());
	y = *(values.begin() + 1);
	z = *(values.begin() + 2);
}

inline bool Vector3::operator==(const Vector3& vector) const
{
	return (x == vector.x && y == vector.y && z == vector.z);
}

inline bool Vector3::operator!=(const Vector3& vector) const
{
	return (x != vector.x || y != vector.y || z != vector.z);
}

inline void Vector3::operator+=(const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

inline void Vector3::operator-=(const Vector3& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
}

inline void Vector3::operator*=(const Vector3& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
}

inline void Vector3::operator/=(numeral value)
{
	if (abs(value) <= EPSILON)
		return;
	x /= value;
	y /= value;
	z /= value;
}

inline void Vector3::operator/=(const Vector3& vector)
{
	if (abs(vector.x) <= EPSILON || abs(vector.y) <= EPSILON || abs(vector.z) <= EPSILON)
		return;
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
}

inline void Vector3::operator*=(numeral value)
{
	x *= value;
	y *= value;
	z *= value;
}

inline const numeral Vector3::operator[](int index) const
{
	if (index > 2)
		assert(false);
	return (&x)[index];
}

inline numeral& Vector3::operator[](int index)
{
	if (index > 2)
	{
		assert(false);
	}
	return (&x)[index];
}

}