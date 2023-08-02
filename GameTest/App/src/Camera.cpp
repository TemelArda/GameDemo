#include "stdafx.h"
#include "../include/Camera.h"
#include "Math/MathUtils.h"

namespace Core
{
Camera::Camera()
{
	SetProjectionMatrix(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0);
	SetViewMatrix({0, 0, -10}, {0, 0, 0}, {0, 1, 0});
}

void Camera::SetProjectionMatrix(const float left, const float right, const float bottom, const float top, const float, const float)
{
	mProjectionMatrix = Core_Math::Ortho(left, right, bottom, top, -1.0f, 1.0f);
}

void Camera::SetViewMatrix(const Core_Math::Vector3& Peye, const Core_Math::Vector3& Pref, const Core_Math::Vector3& up)
{
	mViewMatrix = Core_Math::lookAt(Peye, Pref, up);
}
}
