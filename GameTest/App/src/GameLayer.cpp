#include "stdafx.h"
#include "../include/GameLayer.h"
#include "../include/Renderer/Renderer.h"
#include "../include/System/MeshRendererSystem.h"
#include "../include/System/PhysicsWorld.h"

namespace Core
{
GameLayer::GameLayer(std::shared_ptr<Core_Renderer::Renderer> renderer,
	std::shared_ptr<MeshRendererSystem> meshRenderer,
	std::shared_ptr<PhysicsWorld> physicsWorld,
	std::shared_ptr<Core_ECS::Registry> reg)	:
	Layer("GameLayer"), 
	mMeshRenderer(meshRenderer),
	mPhysicsWorld(physicsWorld),
	mRenderer(renderer),
	mIsEnabled(true)
{
	mScene = std::make_shared<Scene>(reg);
}

void GameLayer::OnAttach()
{
	mScene->Initilize();
}

void GameLayer::OnDetach()
{
	mScene->Shutdown();
}

void GameLayer::OnUpdate(float ts)
{
	if(!mIsEnabled)
		return;
	mPhysicsWorld->Update(ts);
}

void GameLayer::OnRender()
{
	if(!mIsEnabled)
		return;
	
	mRenderer->BeginScene(mScene);
	
	mMeshRenderer->Render();

	mRenderer->EndScene();
}

void GameLayer::OnEvent(IEvent& e)
{
	if (e.GetType() != EventType::Default)
	{
		LOG_INFO("Event Dispatched with wrong type\n Event: { }", e.toString());
		return;
	}
	DemoEvent de = static_cast<DemoEvent&>(e);
	LOG_INFO("testFunction called with: {}", de.GetVariable());
}

void GameLayer::Enable()
{
	mIsEnabled = true;
}

void GameLayer::Disable()
{
	mIsEnabled = false;
}
}
