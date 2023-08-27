#pragma once
#include "../Renderer/Texture.h"
#include "Math/Vector3.h"
#include "Material.h"

namespace Core_Renderer
{
 class Texture;
}

namespace Core
{
class  DefaultMaterial : public Material
{
public:
	Core_Math::Vector3 AmbientColor;

	Core_Math::Vector3 DiffuseColor;

	Core_Math::Vector3 SpecularColor;

	float Shininess;

	std::shared_ptr<Core_Renderer::Texture> Texture;

public:
	DefaultMaterial();

	DefaultMaterial(const std::shared_ptr<Core_Renderer::Shader>& mShader);

	DefaultMaterial(const std::shared_ptr<Core_Renderer::Shader>& mShader, const std::shared_ptr<Core_Renderer::Texture>& t);

	~DefaultMaterial() = default;

	virtual void SetUniforms() const override;

	virtual const MaterialID GetMaterialID() const override
	{
		return mId;
	}

	virtual const Core_Renderer::ProgramID GetShaderID() const override;

private:

	std::shared_ptr<Core_Renderer::Shader> mShader;

	MaterialID mId;
};
}