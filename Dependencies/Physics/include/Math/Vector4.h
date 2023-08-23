#pragma once
#include "MathCommon.h"
#include <initializer_list>
#include <math.h>
#include <assert.h>
#include <utility>


namespace Core_Math
{

class Vector4
{
public:
	numeral x;

	numeral y;

	numeral z;

	numeral w;
public:

	Vector4() noexcept;

	Vector4(numeral value) noexcept;

	Vector4(numeral x, numeral y, numeral z, numeral w) noexcept;

	~Vector4() = default;

	Vector4(const Vector4& vector) noexcept;

	Vector4(Vector4&& vector) noexcept :
		x(std::move(vector.x)),
		y(std::move(vector.y)),
		z(std::move(vector.z)),
		w(std::move(vector.w))
	{
	}

	Vector4& operator=(const Vector4& vector) noexcept = default;

	Vector4& operator=(Vector4&& vector) noexcept = default;

	void operator=(const std::initializer_list<numeral>& values);

	void SetVector4(numeral value) noexcept;

	void SetVector4(numeral x, numeral y, numeral z, numeral w) noexcept;

	void SetToZero() noexcept;

	const numeral Magnitude() const;

	const numeral MagnitudeSquared() const;

	void Normalize();

	Vector4 GetNormalized() const;

	numeral Dot(const Vector4& vector) const;

	bool IsZero() const;

	bool IsNormalized() const;

	bool IsFinite() const;

	bool operator==(const Vector4& vector) const;

	bool operator!=(const Vector4& vector) const;

	void operator+=(const Vector4& vector);

	void operator-=(const Vector4& vector);

	void operator*=(const Vector4& vector);

	void operator*=(numeral value);

	void operator/=(const Vector4& vector);

	void operator/=(numeral value);

	const numeral& operator[](int index) const;

	numeral& operator[](int index);

	// -------------------- Friends -------------------- //

	friend Vector4 operator+(const Vector4& vector1, const Vector4& vector2);
	friend Vector4 operator-(const Vector4& vector1, const Vector4& vector2);
	friend Vector4 operator-(const Vector4& vector);
	friend Vector4 operator*(const Vector4& vector, numeral number);
	friend Vector4 operator*(numeral number, const Vector4& vector);
	friend Vector4 operator*(const Vector4& vector1, const Vector4& vector2);
	friend Vector4 operator/(const Vector4& vector, numeral number);
	friend Vector4 operator/(const Vector4& vector1, const Vector4& vector2);
};

inline Vector4::Vector4() noexcept
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

inline Vector4::Vector4(numeral value) noexcept
	: x(value), y(value), z(value), w(value)
{
}

inline Vector4::Vector4(numeral x, numeral y, numeral z, numeral w) noexcept
	: x(x), y(y), z(z), w(w)
{
}

inline Vector4::Vector4(const Vector4& vector) noexcept
	: x(vector.x), y(vector.y), z(vector.z), w(vector.w)
{
}


inline void Vector4::SetVector4(numeral value) noexcept
{
	x = value;
	y = value;
	z = value;
	w = value;
}

inline void Vector4::SetVector4(numeral x, numeral y, numeral z, numeral w) noexcept
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

inline void Vector4::SetToZero() noexcept
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

inline const numeral Core_Math::Vector4::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

inline const numeral Core_Math::Vector4::MagnitudeSquared() const
{
	return abs(x * x + y * y + z * z + w * w);
}

inline numeral Vector4::Dot(const Vector4& vector) const
{
	return (x * vector.x + y * vector.y + z * vector.z + w * vector.w);
}

inline bool Vector4::IsFinite() const
{
	return isfinite<numeral>(x) && isfinite<numeral>(y) && isfinite<numeral>(z) && isfinite<numeral>(w);
}

inline void Vector4::operator=(const std::initializer_list<numeral>& values)
{
	if (values.size() != 4)
	{
		return;
	}
	x = *(values.begin());
	y = *(values.begin() + 1);
	z = *(values.begin() + 2);
	w = *(values.begin() + 3);
}

inline bool Vector4::operator==(const Vector4& vector) const
{
	return (x == vector.x && y == vector.y && z == vector.z && w == vector.w);
}

inline bool Vector4::operator!=(const Vector4& vector) const
{
	return (x != vector.x || y != vector.y || z != vector.z || w != vector.w);
}

inline void Vector4::operator+=(const Vector4& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
}

inline void Vector4::operator-=(const Vector4& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
}

inline void Vector4::operator*=(const Vector4& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w *= vector.w;
}

inline void Vector4::operator/=(numeral value)
{
	if (abs(value) <= EPSILON)
		return;
	x /= value;
	y /= value;
	z /= value;
	w /= value;
}

inline void Vector4::operator/=(const Vector4& vector)
{
	if (abs(vector.x) <= EPSILON || abs(vector.y) <= EPSILON 
	|| abs(vector.z) <= EPSILON || abs(vector.w) <= EPSILON)
		return;
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	w /= vector.w;
}

inline void Vector4::operator*=(numeral value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
}

inline const numeral& Vector4::operator[](int index) const
{
	if (index > 3)
		assert(false);

	return (&x)[index];
}

inline numeral& Vector4::operator[](int index)
{
	if (index > 3)
		assert(false);

	return (&x)[index];
}

}
