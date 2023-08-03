#include "stdafx.h"
#include "../include/Camera.h"
#include "Math/MathUtils.h"

namespace Core
{
Camera::Camera()
{
	SetProjectionMatrix(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 100.0);
	mTransform.mPosition = { 0, 0, -10 };
	SetViewMatrix();
}

Camera::Camera(Core_Math::Vector3 pos, Core_Math::Vector3 dir)
{
	mTransform.mPosition = pos;
	SetProjectionMatrix(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 100.0);
	SetViewMatrix();
}

Camera::Camera(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	SetProjectionMatrix(left, right, bottom, top, near, far);
	mTransform.mPosition = { 0, 0, -10 };
	SetViewMatrix();
}

void Camera::SetProjectionMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	mProjectionMatrix = Core_Math::Ortho(left, right, bottom, top, near, far);
	mViewxProjection = mProjectionMatrix * mViewMatrix;
}

void Camera::SetViewMatrix()
{
	mViewMatrix = mTransform.GetInverseModelMatrix();
	mViewxProjection = mProjectionMatrix * mViewMatrix;
}

void Camera::SetPosition(const Core_Math::Vector3& position)
{
	mTransform.mPosition = position;
	SetViewMatrix();
}

void Camera::SetRotation(const Core_Math::Vector3& euler)
{
	mTransform.mRotation = Core_Math::Quaternion::Identity();
	mTransform.Rotate(euler);
	SetViewMatrix();
}
}
