#include "stdafx.h"
#include "../include/Material.h"
#include "../include/ResourceManager.h"

namespace Core
{
DefaultMaterial::DefaultMaterial()
	: AmbientColor(.9f), DiffuseColor(.9f), SpecularColor(.9f), SpecularPower(1.0f)
{
	mShader = ResourceManager::GetInstance().GetDefaultShader();
	Texture = ResourceManager::GetInstance().GetWhiteTexture();
}

DefaultMaterial::DefaultMaterial(const std::shared_ptr<Core_Renderer::Shader>& mShader)
	:mShader(mShader), AmbientColor(.9f), DiffuseColor(.9f), SpecularColor(.9f), SpecularPower(1.0f)
{
	Texture = ResourceManager::GetInstance().GetWhiteTexture();
}

DefaultMaterial::DefaultMaterial(const std::shared_ptr<Core_Renderer::Shader>& mShader, const std::shared_ptr<Core_Renderer::Texture>& t)
	:mShader(mShader), Texture(t), AmbientColor(.9f), DiffuseColor(.9f), SpecularColor(.9f), SpecularPower(1.0f)
{
}
}