#include "../../include/Math/Mat4x4.h"

namespace Core_Math
{
inline Mat4x4::Mat4x4() noexcept : 
	mRows(std::make_unique<Vector4[]>(4))
{
}

inline Mat4x4::Mat4x4(numeral value) noexcept :
	mRows(std::make_unique<Vector4[]>(4))
{
	this->SetMatrix(value);
}
Mat4x4::Mat4x4(std::initializer_list<numeral> list) noexcept :
	mRows(std::make_unique<Vector4[]>(4))
{
	if (list.size() != 16)
		return;
	auto it = list.begin();
	for (size_t i = 0; i < 4; ++i)
	{
		mRows[i].SetVector4(*it, *(it + 1), *(it + 2), *(it + 3));
		it += 4;
	}
}
inline Mat4x4::Mat4x4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d) noexcept :
	mRows(std::make_unique<Vector4[]>(4))
{
	mRows[0] = a;
	mRows[1] = b;
	mRows[2] = c;
	mRows[3] = d;
}
inline Mat4x4::Mat4x4(numeral a1, numeral a2, numeral a3, numeral a4,
numeral b1, numeral b2, numeral b3, numeral b4,
numeral c1, numeral c2, numeral c3, numeral c4,
numeral d1, numeral d2, numeral d3, numeral d4) noexcept:
	mRows(std::make_unique<Vector4[]>(4))
{
	mRows[0].SetVector4(a1, a2, a3, a4);
	mRows[1].SetVector4(b1, b2, b3, b4);
	mRows[2].SetVector4(c1, c2, c3, c4);
	mRows[3].SetVector4(d1, d2, d3, d4);
}

Mat4x4::Mat4x4(const Mat4x4& other) noexcept :
	mRows(std::make_unique<Vector4[]>(4))
{
	for (size_t i = 0; i < 4; ++i)
	{
		mRows[i] = other.mRows[i];
	}
}

Mat4x4& Mat4x4::operator=(const Mat4x4& other) noexcept
{
	if (this == &other)
		return *this;
	for (size_t i = 0; i < 4; i++)
	{
		mRows[i] = other.mRows[i];
	}
	return *this;
}

void Mat4x4::SetMatrix(numeral value) noexcept
{
	for (size_t i = 0; i < 4; ++i)
	{
		mRows[i].SetVector4(value);
	}
}
Vector4 Mat4x4::GetRow(int index) const
{
	assert(index >= 0 && index < 4);
	return mRows[index];
}
void Mat4x4::SetRow(int index, const Vector4& row)
{
	assert(index >= 0 && index < 4);
	mRows[index] = row;
}

Vector4 Mat4x4::GetColumn(int index) const
{
	assert(index >= 0 && index < 4);
	return Vector4(mRows[0][index], mRows[1][index], 
		mRows[2][index], mRows[3][index]);
}

void Mat4x4::SetColumn(int index, const Vector4& column)
{
	assert(index >= 0 && index < 4);
	
	mRows[0][index] = column.x;
	mRows[1][index] = column.y;
	mRows[2][index] = column.z;
	mRows[3][index] = column.w;
}

void Mat4x4::SetToZero()
{
	for (size_t i = 0; i < 4; ++i)
	{
		mRows[i].SetToZero();
	}
}
void Mat4x4::SetToIdentity()
{
	for (size_t i = 0; i < 4; ++i)
	{
		mRows[i].SetToZero();
		mRows[i][i] = 1.0;
	}
}
Mat4x4 Mat4x4::Get3x3Part() const
{
    Mat4x4 mat;
	 
	 for (size_t i = 0; i < 2; i++)
	 {
		 for (size_t j = 0; j < 2; j++)
		 {
			 mat.mRows[i][j] = mRows[i][j];
		 }
	 }
	 return mat;
}
void Mat4x4::Transpose()
{
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = i + 1; j < 4; ++j)
		{
			if(i == j)
				continue;
			numeral temp = mRows[i][j];
			mRows[i][j] = mRows[j][i];
			mRows[j][i] = temp;
		}
	}
}

Mat4x4 Mat4x4::Transpose(const Mat4x4& matrix)
{
	return Mat4x4(
		matrix.GetColumn(0), 
		matrix.GetColumn(1),
		matrix.GetColumn(2),
		matrix.GetColumn(3)
		);
}

Mat4x4 Mat4x4::Identity()
{
	
	return Mat4x4(
		1, 0, 0, 0, 
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

Mat4x4 Mat4x4::operator*(const Mat4x4& rhs)
{
	Mat4x4 result = *this;
	result *= rhs;
	return result;
}

Vector4 Mat4x4::operator*(const Vector4& vec)
{
	Vector4 result;

	for (size_t i = 0; i < 4; ++i)
	{
		result[i] = mRows[i].x * vec.x + mRows[i].y * vec.y + mRows[i].z * vec.z + mRows[i].w * vec.w;
	}
	return result;
}
Mat4x4 Mat4x4::operator*(numeral value)
{
	Mat4x4 result = *this;
	result *= value;
	return Mat4x4();
}
} // namespace Core_Math