#include "stdafx.h"
#include "../include/Material.h"
#include "../include/ResourceManager.h"

namespace Core
{
MaterialID DefaultMaterial::mNextMaterialId = 0;

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
inline uint32_t DefaultMaterial::GetShaderID()
{
	return mShader->GetID();
}
}