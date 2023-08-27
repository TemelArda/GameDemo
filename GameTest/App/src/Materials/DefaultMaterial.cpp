#include "stdafx.h"
#include "../../include/Materials/DefaultMaterial.h"
#include "../../include/ResourceManager.h"
#include "../../include/Renderer/Shader.h"

namespace Core
{

DefaultMaterial::DefaultMaterial()
	: AmbientColor(.9f), DiffuseColor(.9f), SpecularColor(.9f), Shininess(1.0f)
{
	mId = mNextMaterialId++;
	mShader = ResourceManager::GetInstance().GetDefaultShader();
	Texture = ResourceManager::GetInstance().GetWhiteTexture();
}

DefaultMaterial::DefaultMaterial(const std::shared_ptr<Core_Renderer::Shader>& mShader)
	:mShader(mShader), AmbientColor(.9f), DiffuseColor(.9f), SpecularColor(.9f), Shininess(1.0f)
{
	mId = mNextMaterialId++;
	Texture = ResourceManager::GetInstance().GetWhiteTexture();
}

DefaultMaterial::DefaultMaterial(const std::shared_ptr<Core_Renderer::Shader>& mShader, const std::shared_ptr<Core_Renderer::Texture>& t)
	:mShader(mShader), Texture(t), AmbientColor(.9f), DiffuseColor(.9f), SpecularColor(.9f), Shininess(1.0f)
{
	mId = mNextMaterialId++;
}

void DefaultMaterial::SetUniforms() const
{
	Texture->Bind();
	Core_Renderer::SetUniform3f(mShader->Id, "u_Ambient_product", AmbientColor);
	Core_Renderer::SetUniform3f(mShader->Id, "u_Diffuse_product", DiffuseColor);
	Core_Renderer::SetUniform3f(mShader->Id, "u_Specular_product", SpecularColor);
	Core_Renderer::SetUniform1f(mShader->Id, "u_Shininess", Shininess);
	Core_Renderer::SetUniform1i(mShader->Id, "u_Texture", 0);
}


inline const Core_Renderer::ProgramID DefaultMaterial::GetShaderID() const
{
	return mShader->Id;
}
}