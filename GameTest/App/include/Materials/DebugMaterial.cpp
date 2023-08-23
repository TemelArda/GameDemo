#include "stdafx.h"
#include "DebugMaterial.h"
#include "../../include/Renderer/Shader.h"
#include "../../include/ResourceManager.h"
namespace Core
{
DebugMaterial::DebugMaterial() : color(1.0f, 1.0f, 1.0f)
{
	mShader = ResourceManager::GetInstance().GetShader("Debug");
	mId = mNextMaterialId++;
}

DebugMaterial::DebugMaterial(Core_Math::Vector3 color) : color(color)
{
	mShader = ResourceManager::GetInstance().GetShader("Debug");
	mId = mNextMaterialId++;
}


void DebugMaterial::Bind()
{
	mShader->Bind();
	mShader->SetUniform3f("u_Color", color);
}

void DebugMaterial::Unbind()
{
	mShader->Unbind();
}

MaterialID DebugMaterial::GetMaterialID()
{
    return mId;
}

uint32_t DebugMaterial::GetShaderID()
{
    return mShader->GetID();
}

std::shared_ptr<Core_Renderer::Shader> DebugMaterial::GetShader() const
{
    return mShader;
}
}
