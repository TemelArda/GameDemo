#include "stdafx.h"
#include "../../include/Materials/PhysicsDebugMaterial.h"
#include "../../include/Renderer/Shader.h"
#include "../../include/ResourceManager.h"

namespace Core
{
PhysicsDebugMaterial::PhysicsDebugMaterial() : 
Color(.5f, .5f, .5f, .5f), WireframeColor(.1, .1, .1), WireframeSmoothing(0.1f), WireframeThickness(1.0f)
{
	const auto& shader = ResourceManager::GetInstance().GetShader("Wireframe");
	if (shader.has_value())
	{
		mShader = shader.value();
	}
	else
	{
		mShader = ResourceManager::GetInstance().LoadShader("Wireframe.glsl", "Wireframe");
	}
	mId = mNextMaterialId++;
}

PhysicsDebugMaterial::PhysicsDebugMaterial(Core_Math::Vector4 color) : 
Color(color), WireframeColor(.1, .1, .1), WireframeSmoothing(0.1f), WireframeThickness(1.0f)
{
	const auto& shader = ResourceManager::GetInstance().GetShader("Wireframe");
	if (shader.has_value())
	{
		mShader = shader.value();
	}
	else
	{
		mShader = ResourceManager::GetInstance().LoadShader("Wireframe.glsl", "Wireframe");
	}
	mId = mNextMaterialId++;
}


void PhysicsDebugMaterial::Bind()
{
	mShader->Bind();
	mShader->SetUniform4f("u_Color", Color);
	mShader->SetUniform3f("u_WireframeColor", WireframeColor);
	mShader->SetUniform1f("u_WireframeSmoothing", WireframeSmoothing);
	mShader->SetUniform1f("u_WireframeThickness", WireframeThickness);
}

void PhysicsDebugMaterial::Unbind()
{
	mShader->Unbind();
}

MaterialID PhysicsDebugMaterial::GetMaterialID()
{
    return mId;
}

uint32_t PhysicsDebugMaterial::GetShaderID()
{
    return mShader->GetID();
}

std::shared_ptr<Core_Renderer::Shader> PhysicsDebugMaterial::GetShader() const
{
    return mShader;
}
}
