#include "../../include/Math/Transform3D.h"
#include "../../include/Math/MathUtils.h"

namespace Core_Math
{

const Mat4x4 Transform3D::GetModelMatrix() const
{
	
	Mat4x4 mm = Mat4x4::Identity();

	mm[0][3] = mPosition.x;
	mm[1][3] = mPosition.y;
	mm[2][3] = mPosition.z;

	Mat4x4 rm = mRotation.toMatrix();
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			mm[i][j] = rm[i][j];
		}
	}

	return mm;
}

const Mat4x4 Transform3D::GetInverseModelMatrix() const
{
	
	Mat4x4 modelMatrixTransposed = Mat4x4::Transpose(GetModelMatrix());
	modelMatrixTransposed.SetRow(3, {0, 0, 0, 1});
	for(int i = 0; i < 3; ++i )
	{
		modelMatrixTransposed[i][3] = -(modelMatrixTransposed[i][0] * mPosition.x + modelMatrixTransposed[i][1] * mPosition.y + modelMatrixTransposed[i][2] * mPosition.z);
	}
	return modelMatrixTransposed;
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