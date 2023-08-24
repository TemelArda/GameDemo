#include "stdafx.h"
#include "../include/Camera.h"
#include "Math/MathUtils.h"
#include "../include/CoreDefines.h"
#include "../include/Settings.h"


namespace Core
{
Camera::Camera()
{
	SetProjectionMatrixToPerspective(PI / 4.0f, APP_ASPECT_RATIO, 0.1f, 100.0f);
	mTransform.mPosition = { 0.0f, 0.0f, 10 };
	mTransform.mRotation = Core_Math::Quaternion::FromEuler({ 0.0f, PI, 0.0f });
	SetViewMatrix();
}

Camera::Camera(Core_Math::Vector3 pos, Core_Math::Vector3 dir)
{
	SetProjectionMatrixToPerspective(PI / 4.0f, APP_ASPECT_RATIO, 0.1f, 100.0f);
	mTransform.mPosition = pos;
	mTransform.mRotation = Core_Math::Quaternion::FromEuler(dir);
	SetViewMatrix();
}

void Camera::SetProjectionMatrixToOrtho(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	mProjectionMatrix = Core_Math::Ortho(left, right, bottom, top, near, far);
	mViewxProjection = mProjectionMatrix * mViewMatrix;
}

void Camera::SetViewMatrix()
{
	mViewMatrix = mTransform.GetInverseModelMatrix();
	mViewxProjection = mProjectionMatrix * mViewMatrix;
}

void Camera::SetProjectionMatrixToPerspective(const float fov, const float aspectRatio, const float n, const float f)
{
	mProjectionMatrix = Core_Math::Perspective(fov, aspectRatio, n, f);
	mViewxProjection = mProjectionMatrix * mViewMatrix;
}

void Camera::SetPosition(const Core_Math::Vector3& position)
{
	mTransform.mPosition = position;
	SetViewMatrix();
}

void Camera::SetRotation(const Core_Math::Vector3& euler)
{
	mTransform.mRotation = Core_Math::Quaternion::FromEuler(euler);
	SetViewMatrix();
}
}
