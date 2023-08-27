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


void PhysicsDebugMaterial::SetUniforms() const
{
	Core_Renderer::SetUniform4f(mShader->Id, "u_Color", Color);
	Core_Renderer::SetUniform3f(mShader->Id, "u_WireframeColor", WireframeColor);
	Core_Renderer::SetUniform1f(mShader->Id, "u_WireframeSmoothing", WireframeSmoothing);
	Core_Renderer::SetUniform1f(mShader->Id, "u_WireframeThickness", WireframeThickness);
}

const MaterialID PhysicsDebugMaterial::GetMaterialID() const
{
    return mId;
}

const Core_Renderer::ProgramID PhysicsDebugMaterial::GetShaderID() const
{
    return mShader->Id;
}

}
