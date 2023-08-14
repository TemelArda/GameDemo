#pragma once
#include "MathCommon.h"
#include "Vector2.h"
#include "Mat4x4.h"

namespace Core_Math
{
class Transform2D
{
public:

	Vector2 mPosition;
	
	numeral mRotation;
	
	Vector2 mScale;

	Transform2D();

	Transform2D(const Vector2& pos, numeral rot, const Vector2 scale);

	~Transform2D() = default;

	Transform2D(const Transform2D& transform) noexcept :
		mPosition(transform.mPosition),
		mRotation(transform.mRotation),
		mScale(transform.mScale)
	{
	}

	Transform2D(Transform2D&& transform) noexcept :
		mPosition(std::move(transform.mPosition)),
		mRotation(std::move(transform.mRotation)),
		mScale(std::move(transform.mScale))
	{
	}

	Transform2D& operator=(const Transform2D& transform) noexcept = default;

	Transform2D& operator=(Transform2D&& transform) noexcept = default;

	const Mat4x4& GetModelMatrix() const;

	const Mat4x4& GetInverseModelMatrix() const;

	void Translate(const Vector2& translation);

	void Rotate(numeral angle);

	void Scale(const Vector2& scale);
};

Transform2D::Transform2D()
{
	mPosition = Vector2(0.0f, 0.0f);
	mRotation = 0.0f;
	mScale = Vector2(1.0f, 1.0f);
}

Transform2D::Transform2D(const Vector2& pos, numeral rot, const Vector2 scale)
	: mPosition(pos), mRotation(rot), mScale(scale)
{
}

inline const Mat4x4& Transform2D::GetModelMatrix() const
{
	Mat4x4 ModelMatrix = Mat4x4::Identity();
	
	ModelMatrix[0][0] *= cos(mRotation) * mScale.x;
	ModelMatrix[0][1] = -sin(mRotation);
	ModelMatrix[0][3] = mPosition.x;

	ModelMatrix[1][0] = sin(mRotation);
	ModelMatrix[1][1] *= cos(mRotation) * mScale.y;
	ModelMatrix[1][3] = mPosition.y;

	return ModelMatrix;
}
//[ux uy uz - dot(u, t)]
//[vx vy vz - dot(v, t)]
//[wx wy wz - dot(w, t)]
//[0  0  0     1]
inline const Mat4x4& Transform2D::GetInverseModelMatrix() const
{
	Mat4x4 modelMatrix = GetModelMatrix();
	Mat4x4 inverseModelMatrix = Mat4x4::Identity();

	inverseModelMatrix [0][0] = modelMatrix[0][0];
	inverseModelMatrix [0][1] = modelMatrix[1][0];
	inverseModelMatrix [0][2] = 0;
	inverseModelMatrix [0][3] = -(modelMatrix[0][0] * mPosition.x + modelMatrix[1][0] * mPosition.y);
	inverseModelMatrix [1][0] = modelMatrix[0][1];
	inverseModelMatrix [1][1] = modelMatrix[1][1];
	inverseModelMatrix [1][2] = 0;
	inverseModelMatrix [1][3] = -(modelMatrix[0][1] * mPosition.x + modelMatrix[1][1] * mPosition.y);

	return inverseModelMatrix;
}

inline void Transform2D::Translate(const Vector2& translation)
{
	mPosition += translation;
}

inline void Transform2D::Rotate(numeral angle)
{
	mRotation += angle;
}

inline void Transform2D::Scale(const Vector2& scale)
{
	mScale *= scale;
}

}
