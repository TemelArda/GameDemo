#include "stdafx.h"
#include "../../include/Layers/DebugLayer.h"
#include "../../include/Renderer/Renderer.h"
#include "../../include/System/PhysicsWorld.h"
#include "../../include/Mesh.h"
#include "../../include/ResourceManager.h"
#include "../../include/Materials/PhysicsDebugMaterial.h"
#include "Logger.h"

namespace Core
{
DebugLayer::DebugLayer(std::shared_ptr<Core_Renderer::Renderer> renderer, 
	std::shared_ptr<PhysicsWorld> physicsWorld) :
	Layer("Debug"),
	mRenderer(renderer), 
	mPhysicsWorld(physicsWorld), 
	mIsEnabled(true)
{}

void DebugLayer::OnAttach()
{
	using Color = Core_Math::Vector4;

	std::shared_ptr<PhysicsDebugMaterial> debugMaterial = std::make_shared<PhysicsDebugMaterial>(Color(0.0f, .75f, 0.2f, 0.05));
	debugMaterial->WireframeColor = Core_Math::Vector3(0.15, 0.5, 0.15);
	debugMaterial->WireframeThickness = 0.25f;
	ResourceManager::GetInstance().LoadMaterial(debugMaterial, "PhysicsDebug");
	const auto& physicsVertexArray = ResourceManager::GetInstance().GetVertexArray("Sphere");
	if(!physicsVertexArray.has_value())
	{
		LOG_ERROR("Physics debug mesh couldn't be loaded");
		return;
	}
	const auto& physicsDebugMesh = std::make_shared<Mesh>(physicsVertexArray.value(), debugMaterial);
	
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
