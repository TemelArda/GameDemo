#include "../../include/Math/Transform3D.h"
#include "../../include/Math/MathUtils.h"

namespace Core_Math
{

inline const Mat4x4& Transform3D::GetModelMatrix() const
{
	Mat4x4 rotationMatrix = mRotation.toMatrix();

	Mat4x4 scaleMatrix = Mat4x4::Identity();
	scaleMatrix[0][0] = mScale.x;
	scaleMatrix[1][1] = mScale.y;
	scaleMatrix[2][2] = mScale.z;

	Mat4x4 translationMatrix = Mat4x4::Identity();
	translationMatrix[0][3] = mPosition.x;
	translationMatrix[1][3] = mPosition.y;
	translationMatrix[2][3] = mPosition.z;

	return translationMatrix * rotationMatrix * scaleMatrix;
}

inline const Mat4x4& Transform3D::GetInverseModelMatrix() const
{
	Mat4x4 rotationMatrix = mRotation.GetInverse().toMatrix();

	Mat4x4 scaleMatrix = Mat4x4::Identity();
	scaleMatrix[0][0] = 1.0f / mScale.x;
	scaleMatrix[1][1] = 1.0f / mScale.y;
	scaleMatrix[2][2] = 1.0f / mScale.z;

	Mat4x4 translationMatrix = Mat4x4::Identity();
	translationMatrix[0][3] = -mPosition.x;
	translationMatrix[1][3] = -mPosition.y;
	translationMatrix[2][3] = -mPosition.z;

	return scaleMatrix * rotationMatrix * translationMatrix;
}

void Transform3D::Translate(const Vector3& translation)
{
	mPosition += translation;
}

void Transform3D::Rotate(const Quaternion& rotation)
{
	mRotation *= rotation;
}

void Transform3D::Rotate(numeral angle, const Vector3& axis)
{
	mRotation *= Quaternion::FromAxisAngle(axis, angle);
}

void Transform3D::Rotate(const Vector3& euler)
{
	mRotation *= Quaternion::FromEuler(euler);
}

void Transform3D::Scale(const Vector3& scale)
{
	mScale *= scale;
}

void Transform3D::LookAt(const Vector3& target, const Vector3& up)
{
	const auto& m  = lookAt(mPosition, target, up);
	mRotation = Quaternion::FromMatrix(m);
	mPosition = m[0].w;
	mPosition = m[1].w;
	mPosition = m[2].w;

}


} // namespace Core_Math