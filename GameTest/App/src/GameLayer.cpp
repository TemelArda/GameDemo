#include "stdafx.h"
#include "../include/GameLayer.h"
#include "../include/ResourceManager.h"
#include "ECS.h"
#include "../include/Material.h"
#include "Math/Transform3D.h"
#include "../include/Camera.h"
#include "../include/Renderer/Renderer.h"
#include "../include/Mesh.h"



namespace Core
{
GameLayer::GameLayer(std::shared_ptr<Core_Renderer::Renderer> renderer, std::shared_ptr<Core_ECS::Registry> reg)
	: Layer("GameLayer"), mRenderer(renderer), mIsEnabled(true)
{
	mScene = std::make_shared<Scene>(reg);
}

void GameLayer::OnAttach()
{
	mScene->Initilize();
}

void GameLayer::OnDetach()
{
	//mScene->Shutdown();
}

void GameLayer::OnUpdate(float ts)
{
	if(!mIsEnabled)
		return;
	mScene->Update(ts);
}

void GameLayer::OnRender()
{
	if(!mIsEnabled)
		return;
	Core_Math::Transform3D transform;
	mRenderer->BeginScene(mScene);
	for (size_t i = 0; i < mMeshes.size(); ++i)
	{
		float x = (float)i - (mMeshes.size() * 0.5f);
		transform.mPosition = { -x , 0.0f, 0.0f };
		mRenderer->Submit(mMeshes[i], transform.GetModelMatrix());
	}

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

	//Create Texture
	const auto& texture = ResourceManager::LoadTexture("blue_eyes.bmp", "BlueEyes");

	//Create Materials
	const auto& material = std::make_shared<DefaultMaterial>();
	material->Texture = texture;
	ResourceManager::LoadMaterial(material, "BlueEyes");

	const auto& materialRed = std::make_shared<DefaultMaterial>();
	materialRed->Texture = texture;
	materialRed->DiffuseColor = { .85f, .1f, .05f, 1.0f };
	ResourceManager::LoadMaterial(materialRed, "RedEyes");

	// create Meshes
	const auto& meshCube = std::make_shared<Mesh>(ResourceManager::GetInstance().GetCubeVertexArray(), material);
	const auto& meshQuad = std::make_shared<Mesh>(ResourceManager::GetInstance().GetQuadVertexArray(), materialRed);

	//default mesh
	mMeshes.push_back(std::make_shared <Mesh>());
	mMeshes.push_back(meshCube);
	mMeshes.push_back(meshQuad);
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
