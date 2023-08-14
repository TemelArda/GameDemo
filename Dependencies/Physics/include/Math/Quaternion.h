#pragma once
#include "MathCommon.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Mat4x4.h"
#include <tuple>
#include <math.h>
#include <assert.h>


namespace Core_Math
{
class Quaternion
{
public:
	numeral x;
	
	numeral y;
	
	numeral z;
	
	numeral w;

	Quaternion();

	Quaternion(numeral x, numeral y, numeral z, numeral w);

	Quaternion(const Vector4& values);
	
	~Quaternion() = default;

	Quaternion(const Quaternion& quaternion) noexcept :
		x(quaternion.x),
		y(quaternion.y),
		z(quaternion.z),
		w(quaternion.w)
	{
	}

	Quaternion(Quaternion&& quaternion) noexcept :
		x(std::move(quaternion.x)),
		y(std::move(quaternion.y)),
		z(std::move(quaternion.z)),
		w(std::move(quaternion.w))
	{
	}

	Quaternion& operator=(const Quaternion& quaternion) noexcept = default;

	Quaternion& operator=(Quaternion&& quaternion) noexcept = default;

	void Set(numeral x, numeral y, numeral z, numeral w);

	void Set(const Vector4& values);

	const std::tuple<numeral, const Vector3> toAxisAngle() const;

	const Vector3 toEuler() const;

	const Mat4x4 toMatrix() const;

	const numeral Magnitude() const;

	const numeral MagnitudehSquare() const;

	Quaternion GetNormilized () const;

	Quaternion GetInverse() const;

	Quaternion GetConjugate() const;

	void normalize();

	void invert();

	void operator*=(const Quaternion& other);

	void operator*=(numeral scalar);

	Vector3 operator*(const Vector3& other) const;

	Quaternion operator*(const Quaternion& other) const;

	inline Quaternion operator*(numeral other) const;

	bool operator==(const Quaternion& quaternion) const;

	static Quaternion Identity()
	{
		return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Quaternion dot(const Quaternion& q1, const Quaternion& q2);

	static Quaternion FromEuler(const Vector3& euler);

	static Quaternion FromEuler(numeral x, numeral y, numeral z);

	static Quaternion FromAxisAngle(const Vector3& axis, numeral angle);

	static Quaternion FromMatrix(const Mat4x4& mat);

	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, numeral t);

	static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, numeral t);
};

inline Quaternion::Quaternion()
	: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
}

inline Quaternion::Quaternion(numeral x, numeral y, numeral z, numeral w)
	: x(x), y(y), z(z), w(w)
{
	
}

inline Quaternion::Quaternion(const Vector4& values)
	: x(values.x), y(values.y), z(values.z), w(values.w)
{
}

void inline Quaternion::Set(numeral x, numeral y, numeral z, numeral w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void inline Quaternion::Set(const Vector4& values)
{
	x = values.x;
	y = values.y;
	z = values.z;
	w = values.w;
}

inline const numeral Core_Math::Quaternion::Magnitude() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}
inline const numeral Core_Math::Quaternion::MagnitudehSquare() const
{
	return (x * x + y * y + z * z + w * w);
}

inline Quaternion Quaternion::GetNormilized() const
{
	numeral m = Magnitude();

	assert(m > EPSILON);
	return Quaternion(x/m, y/m, z/m, w/m);
}

inline Quaternion Quaternion::GetInverse() const
{
	numeral sm = MagnitudehSquare();

	assert(sm > EPSILON);

	return Quaternion(-x/sm, -y/sm, -z/sm, w/sm);
}

inline Quaternion Quaternion::GetConjugate() const
{
	return Quaternion(-x, -y, -z, w);
}

inline void Quaternion::normalize() {

	numeral m = Magnitude();

	assert(m > EPSILON);

	x /= m;
	y /= m;
	z /= m;
	w /= m;
}
inline void Quaternion::invert()
{
	numeral sm = MagnitudehSquare();

	assert(sm > EPSILON);

	x = -x / sm;
	y = -y / sm;
	z = -z / sm;
	w = w / sm;
}

inline void Quaternion::operator*=(const Quaternion& other)
{
		x = w * other.x + other.w * x + y * other.z - z * other.y;
		y = w * other.y + other.w * y + z * other.x - x * other.z;
		z = w * other.z + other.w * z + x * other.y - y * other.x;
		w = w * other.w - x * other.x - y * other.y - z * other.z;
}

inline void Quaternion::operator*=(numeral scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;
}

inline Vector3 Quaternion::operator*(const Vector3& point) const
{
	const numeral prodX = w * point.x + y * point.z - z * point.y;
	const numeral prodY = w * point.y + z * point.x - x * point.z;
	const numeral prodZ = w * point.z + x * point.y - y * point.x;
	const numeral prodW = -x * point.x - y * point.y - z * point.z;
	return Vector3(w * prodX - prodY * z + prodZ * y - prodW * x,
		w * prodY - prodZ * x + prodX * z - prodW * y,
		w * prodZ - prodX * y + prodY * x - prodW * z);
}


inline Quaternion Quaternion::operator*(const Quaternion& other) const
{
	return Quaternion(w * other.x + other.w * x + y * other.z - z * other.y,
		w * other.y + other.w * y + z * other.x - x * other.z,
		w * other.z + other.w * z + x * other.y - y * other.x,
		w * other.w - x * other.x - y * other.y - z * other.z);
}

inline Quaternion Quaternion::operator*(numeral other) const
{
	return Quaternion(x * other, y * other, z * other, w * other);
}

inline bool Quaternion::operator==(const Quaternion& quaternion) const {
	return (x == quaternion.x && y == quaternion.y &&
		z == quaternion.z && w == quaternion.w);
}

inline Quaternion Quaternion::dot(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w);
}
}