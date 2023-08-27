#include "stdafx.h"
#include "../../include/Materials/SkyboxMaterial.h"
#include "../../include/Renderer/Shader.h"
#include "../../include/ResourceManager.h"
#include "../../include/Renderer/Cubemap.h"


namespace Core
{

SkyboxMaterial::SkyboxMaterial()
{
	mId = mNextMaterialId++;
	const auto texture = ResourceManager::GetInstance().GetTexture("Skybox").value();
	Cubemap = std::static_pointer_cast<Core_Renderer::Cubemap>(texture);
	mShader = ResourceManager::GetInstance().GetShader("Skybox").value();
}

void SkyboxMaterial::SetUniforms() const
{
	Cubemap->Bind();
	Core_Renderer::SetUniform1i(mShader->Id, "u_Skybox", 0);
}

const MaterialID Core::SkyboxMaterial::GetMaterialID() const
{
    return mId;
}

const uint32_t Core::SkyboxMaterial::GetShaderID() const
{
    return mShader->Id;
}
}
