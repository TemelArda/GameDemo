#pragma once
#include "Math/Transform3D.h"

namespace Core
{
class Camera
{
public:
	Camera();

	Camera(Core_Math::Vector3 pos, Core_Math::Vector3 dir);

	~Camera() = default;

	void SetProjectionMatrixToOrtho(const float left, const float right, const float bottom, const float top, const float n, const float f);

	void SetProjectionMatrixToPerspective(const float fov, const float aspectRatio, const float n, const float f);

	void SetPosition(const Core_Math::Vector3& position);

	void SetRotation(const Core_Math::Vector3& rotation);

	const Core_Math::Mat4x4& GetProjectionMatrix() const;

	const Core_Math::Mat4x4& GetViewMatrix() const;

	const Core_Math::Mat4x4& GetViewProjection() const;

	const Core_Math::Vector3& GetPosition() const;

	const Core_Math::Quaternion& GetRotation() const;

	const Core_Math::Vector3& GetForwardDirection() const;

	void Translate(const Core_Math::Vector3& translation){ mTransform.Translate(translation); SetViewMatrix(); }

	void Rotate(const Core_Math::Vector3& rotation){ mTransform.Rotate(rotation); SetViewMatrix(); }

	void LookAt(const Core_Math::Vector3& target){ Core_Math::LookAt(mTransform, target, {0, 1, 0}); SetViewMatrix(); }

private:
	
	void SetViewMatrix();
	
	Core_Math::Mat4x4 mProjectionMatrix;

	Core_Math::Mat4x4 mViewMatrix;

	Core_Math::Mat4x4 mViewxProjection;
	
	Core_Math::Transform3D mTransform;
};
const inline Core_Math::Mat4x4& Camera::GetProjectionMatrix() const { return mProjectionMatrix; }

const inline Core_Math::Mat4x4& Camera::GetViewMatrix() const { return mViewMatrix; }

const inline Core_Math::Mat4x4& Camera::GetViewProjection() const { return mViewxProjection; }

const inline Core_Math::Vector3& Camera::GetPosition() const { return mTransform.mPosition; }

const inline Core_Math::Vector3& Camera::GetForwardDirection() const { return mTransform.GetForwardDirection(); }

const inline Core_Math::Quaternion& Camera::GetRotation() const{ return mTransform.mRotation; };
}