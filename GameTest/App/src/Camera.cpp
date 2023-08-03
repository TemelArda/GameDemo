#include "stdafx.h"
#include "../include/Camera.h"
#include "Math/MathUtils.h"

namespace Core
{
Camera::Camera()
{
	SetProjectionMatrix(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0);
	mPosition = {0, 0, -10};
	mDirection = {0, 0, -1};
	Core_Math::Vector3 target = mPosition + mDirection;
	target.Normalize();
	SetViewMatrix(mPosition, target, {0, 1, 0});
}

Camera::Camera(Core_Math::Vector3 pos, Core_Math::Vector3 dir)
	: mPosition(pos), mDirection(dir)
{
	SetProjectionMatrix(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0);
	Core_Math::Vector3 target = mPosition + mDirection;
	target.Normalize();
	SetViewMatrix(mPosition, target, { 0, 1, 0 });
}

Camera::Camera(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	SetProjectionMatrix(left, right, bottom, top, near, far);
	mPosition = { 0, 0, -10 };
	mDirection = { 0, 0, -1 };
	Core_Math::Vector3 target = mPosition + mDirection;
	target.Normalize();
	SetViewMatrix(mPosition, target, { 0, 1, 0 });
}

void Camera::SetProjectionMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	mProjectionMatrix = Core_Math::Ortho(left, right, bottom, top, near, far);
	mViewxProjection = mProjectionMatrix * mViewMatrix;
}

void Camera::SetViewMatrix(const Core_Math::Vector3& Peye, const Core_Math::Vector3& Pref, const Core_Math::Vector3& up)
{
	mViewMatrix = Core_Math::lookAt(Peye, Pref, up);
	mViewxProjection = mProjectionMatrix * mViewMatrix;
}

void Camera::SetPosition(const Core_Math::Vector3& position)
{
	mPosition = position;
	Core_Math::Vector3 target = mPosition + mDirection;
	target.Normalize();
	SetViewMatrix(mPosition, target, { 0, 1, 0 });
}

void Camera::SetForwardDirection(const Core_Math::Vector3& direction)
{
	mDirection = direction;
	Core_Math::Vector3 target = mPosition + mDirection;
	target.Normalize();
	SetViewMatrix(mPosition, target, {0, 1, 0});
}
}
