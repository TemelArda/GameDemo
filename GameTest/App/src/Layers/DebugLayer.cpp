#include "stdafx.h"
#include "../../include/Layers/DebugLayer.h"
#include "../../include/Renderer/Renderer.h"
#include "../../include/System/PhysicsWorld.h"
#include "../../include/Mesh.h"
#include "../../include/ResourceManager.h"
#include "../../include/Materials/DebugMaterial.h"

namespace Core
{
DebugLayer::DebugLayer(std::shared_ptr<Core_Renderer::Renderer> renderer, 
	std::shared_ptr<PhysicsWorld> physicsWorld) :
	Layer("Debug"),
	mRenderer(renderer), 
	mPhysicsWorld(physicsWorld), 
	mIsEnabled(false)
{}

void DebugLayer::OnAttach()
{
	using Color = Core_Math::Vector3;

	ResourceManager::GetInstance().LoadShader("Outline.glsl", "Debug");
	
	std::shared_ptr<DebugMaterial>aabbMaterial = std::make_shared<DebugMaterial>(Color(0.0f, 1.0f, 0.0f));
	ResourceManager::GetInstance().LoadMaterial(aabbMaterial, "AABB");

	const auto& physicsDebugMesh = std::make_shared<Mesh>(ResourceManager::GetInstance().GetCubeVertexArray(), aabbMaterial);
	
	mRenderer->SetAABBDebugMesh(physicsDebugMesh);
}

void DebugLayer::OnDetach()
{
}
void DebugLayer::OnUpdate(float ts)
{
	if(!mIsEnabled)
		return;
}

void DebugLayer::OnRender()
{
	if (mIsEnabled)
	{	
		mRenderer->SubmitAABBObject();
	}
}

void DebugLayer::OnEvent(IEvent& e)
{
}

void DebugLayer::Enable()
{
	mIsEnabled = true;
}

void DebugLayer::Disable()
{
	mIsEnabled = false;
}
}
