#pragma once
#include "Math/Vector3.h"
#include "Math/Mat4x4.h"

namespace Core
{
class Camera
{
public:
	Camera();

	~Camera() = default;

	void SetProjectionMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far);

	void SetViewMatrix(const Core_Math::Vector3& Peye, const Core_Math::Vector3& Pref, const Core_Math::Vector3& up);

	const inline Core_Math::Mat4x4& GetProjectionMatrix() const {return mProjectionMatrix;}

	const inline Core_Math::Mat4x4& GetViewMatrix() const {return mViewMatrix;}

private:
	Core_Math::Mat4x4 mProjectionMatrix;

	Core_Math::Mat4x4 mViewMatrix;
};
}