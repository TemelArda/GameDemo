#pragma once
#include "MathCommon.h"
#include "Vector3.h"
#include "Mat4x4.h"
#include "Quaternion.h"

namespace Core_Math
{
class Transform3D
{
public:
	Vector3 mPosition;

	Quaternion mRotation;

	Vector3 mScale;

	Transform3D();

	Transform3D(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

	~Transform3D() = default;

	const Vector3& GetEulerAngles() const;

	const Vector3& GetForwardDirection() const;

	const Vector3& GetRightDirection() const;

	const Mat4x4& GetModelMatrix() const;

	const Mat4x4& GetInverseModelMatrix() const;

	void Translate(const Vector3& translation);

	void Rotate(const Quaternion& rotation);

	void Rotate(numeral angle, const Vector3& axis);

	void Rotate(const Vector3& euler);

	void Scale(const Vector3& scale);

	void LookAt(const Vector3& target, const Vector3& up);
};

Transform3D::Transform3D()
{
	mPosition = Vector3(0.0f, 0.0f, 0.0f);
	mRotation = Quaternion::Identity();
	mScale = Vector3(1.0f, 1.0f, 1.0f);
}

Transform3D::Transform3D(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
	: mPosition(position), mRotation(rotation), mScale(scale)
{
}

inline const Vector3& Transform3D::GetEulerAngles() const
{
	return mRotation.toEuler();
}

inline const Vector3& Transform3D::GetForwardDirection() const
{
	const auto& v = mRotation.toMatrix();
	return { v[2][0], v[2][1], v[2][2] };
}

inline const Vector3& Transform3D::GetRightDirection() const
{
	const auto& v = mRotation.toMatrix();
	return {v[0][0], v[0][1], v[0][2] };
}
} // namespace Core_Math