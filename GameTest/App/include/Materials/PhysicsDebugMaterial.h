#pragma once
#include "Material.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

namespace Core
{
class PhysicsDebugMaterial : public Material
{
public:
	Core_Math::Vector4 Color;

	Core_Math::Vector3 WireframeColor;
	
	float WireframeSmoothing;
	
	float WireframeThickness;

	PhysicsDebugMaterial();

	PhysicsDebugMaterial(Core_Math::Vector4 color);

	virtual void Bind() override;
	
	virtual void Unbind() override;
	
	virtual MaterialID GetMaterialID() override;
	
	virtual uint32_t GetShaderID() override;
	
	virtual std::shared_ptr<Core_Renderer::Shader> GetShader() const override;

private:
	std::shared_ptr<Core_Renderer::Shader> mShader;

	MaterialID mId;
};

}