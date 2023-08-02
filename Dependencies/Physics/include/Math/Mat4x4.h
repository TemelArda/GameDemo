#pragma once
#include "MathCommon.h"
#include <initializer_list>
#include "Vector4.h"
#include <cassert>

namespace Core_Math
{
class Mat4x4
{
public:
	Mat4x4();

	Mat4x4(numeral value);

	Mat4x4(std::initializer_list<numeral> list);

	Mat4x4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d);

	Mat4x4(
		numeral a1, numeral a2, numeral a3, numeral a4,
		numeral b1, numeral b2, numeral b3, numeral b4,
		numeral c1, numeral c2, numeral c3, numeral c4,
		numeral d1, numeral d2, numeral d3, numeral d4
		);

	~Mat4x4() = default;

	Mat4x4(const Mat4x4& other);

	void SetMatrix(numeral value);

	Vector4 GetRow(int index) const;

	void SetRow(int index, const Vector4& row);

	Vector4 GetColumn(int index) const;

	void SetColumn(int index, const Vector4& column);

	void SetToZero();

	void SetToIdentity();

	void Transpose();

	static Mat4x4 Transpose(const Mat4x4& matrix);

	static Mat4x4 GetIdentity();

	const Vector4& operator[](int i) const;

	Vector4& operator[](int i);

	void operator*=(const Mat4x4& other);

	void operator*=(numeral value);

	Mat4x4 operator*(const Mat4x4& other);

	Vector4 operator*(const Vector4& vec);
private:
	Vector4 mRows[4];
};

const inline Vector4& Mat4x4::operator[](int i) const
{
	if (i > 3) 
		assert(false);

	return mRows[i];
}

inline Vector4& Mat4x4::operator[](int i)
{
	if (i > 3)
		assert(false);

	return mRows[i];
}

inline void Mat4x4::operator*=(const Mat4x4& other)
{	
	for (size_t i = 0; i < 4; ++i)
	{
		mRows[i]  = Vector4(
			mRows[i].x * other[0].x + mRows[i].y * other[1].x + mRows[i].z * other[2].x + mRows[i].w * other[3].x,
			mRows[i].x * other[0].y + mRows[i].y * other[1].y + mRows[i].z * other[2].y + mRows[i].w * other[3].y,
			mRows[i].x * other[0].z + mRows[i].y * other[1].z + mRows[i].z * other[2].z + mRows[i].w * other[3].z,
			mRows[i].x * other[0].w + mRows[i].y * other[1].w + mRows[i].z * other[2].w + mRows[i].w * other[3].w
		);
	}
}

inline void Mat4x4::operator*=(numeral value)
{
	for (size_t i = 0; i < 4; ++i)
	{
		mRows[i] *= value;
	}
}
}