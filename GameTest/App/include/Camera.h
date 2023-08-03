#pragma once
#include "Math/Vector3.h"
#include "Math/Mat4x4.h"

namespace Core
{
class Camera
{
public:
	Camera();

	Camera(Core_Math::Vector3 pos, Core_Math::Vector3 dir);

	Camera(const float left, const float right, const float bottom, const float top, const float n, const float f);

	~Camera() = default;

	void SetProjectionMatrix(const float left, const float right, const float bottom, const float top, const float n, const float f);

	void SetPosition(const Core_Math::Vector3& position);

	void SetForwardDirection(const Core_Math::Vector3& direction);

	const inline Core_Math::Mat4x4& GetProjectionMatrix() const;

	const inline Core_Math::Mat4x4& GetViewMatrix() const;

	const inline Core_Math::Mat4x4& GetViewProjection() const;

	const inline Core_Math::Vector3& GetPosition() const;

	const inline Core_Math::Vector3& GetForwardDirection() const;

private:
	
	void SetViewMatrix(const Core_Math::Vector3& Peye, const Core_Math::Vector3& Pref, const Core_Math::Vector3& up);
	
	Core_Math::Mat4x4 mProjectionMatrix;

	Core_Math::Mat4x4 mViewMatrix;

	Core_Math::Mat4x4 mViewxProjection;
	
	Core_Math::Vector3 mPosition;

	Core_Math::Vector3 mDirection;
};
const inline Core_Math::Mat4x4& Camera::GetProjectionMatrix() const { return mProjectionMatrix; }

const inline Core_Math::Mat4x4& Camera::GetViewMatrix() const { return mViewMatrix; }

const inline Core_Math::Mat4x4& Camera::GetViewProjection() const { return mViewxProjection; }

const inline Core_Math::Vector3& Camera::GetPosition() const { return mPosition; }

const inline Core_Math::Vector3& Camera::GetForwardDirection() const { return mDirection; }
}