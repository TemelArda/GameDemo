#pragma once
#include "Material.h"

namespace Core_Renderer
{
class Cubemap;
}

namespace Core
{
class SkyboxMaterial : public Material
{

public:
	std::shared_ptr<Core_Renderer::Cubemap> Cubemap;

	SkyboxMaterial();

	virtual void SetUniforms() const override;
		
	virtual const MaterialID GetMaterialID() const override;
	
	virtual const Core_Renderer::ProgramID GetShaderID() const override;

private:
	MaterialID mId;

	std::shared_ptr<Core_Renderer::Shader> mShader;

};
}