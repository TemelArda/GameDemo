#pragma once
#include "Material.h"
#include "Math/Vector3.h"


namespace Core
{
class DebugMaterial : public Material
{
public:
	Core_Math::Vector3 color;
	DebugMaterial();

	DebugMaterial(Core_Math::Vector3 color);

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