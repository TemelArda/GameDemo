#include "stdafx.h"
#include "../include/GameLayer.h"
#include "../include/ResourceManager.h"
#include "ECS.h"
#include "../include/Material.h"
#include "Math/Transform3D.h"
#include "../include/Camera.h"
#include "../include/Renderer/Renderer.h"
#include "../include/Mesh.h"
#include "../include/CoreDefines.h"


namespace Core
{
GameLayer::GameLayer(std::shared_ptr<Core_Renderer::Renderer> renderer, std::shared_ptr<Core_ECS::Registry> reg)
	: Layer("GameLayer"), mRenderer(renderer), mIsEnabled(true)
{
	mScene = std::make_shared<Scene>(reg);
}

void GameLayer::OnAttach()
{
	ResourceManager::GetInstance().Initilize();
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
	for (int i = 0; i < mMeshes.size(); ++i)
	{
		float x = (- i + (int)mMeshes.size() / 2) * 2;
		transform.mPosition = { x , 0.0f, 0.0f };
		transform.Rotate({0.0f, mScene->GetElapsedTimeInMilliSeconds() / 100 * PI / 180, 0.0f});
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
	const auto& textureMonkey = ResourceManager::LoadTexture("monkeytexture.bmp", "MonkeyTex");

	//Create Materials
	const auto& materialTextured = std::make_shared<DefaultMaterial>();
	materialTextured->Texture = texture;
	materialTextured->DiffuseColor = { .85f, .85f, .85f };
	materialTextured->AmbientColor = { .85f, .85f, .85f };
	materialTextured->SpecularColor = { .85f, .85f, .85f };
	materialTextured->Shininess = 1.0f;
	ResourceManager::LoadMaterial(materialTextured, "BlueEyes");

	const auto& materialRed = std::make_shared<DefaultMaterial>();
	materialRed->Texture = texture;
	materialRed->DiffuseColor = {.85f, .1f, .05f};
	materialRed->AmbientColor = {.85f, .1f, .05f};
	materialRed->SpecularColor = {.85f, .1f, .05f};
	materialRed->Shininess = 10.0f;
	ResourceManager::LoadMaterial(materialRed, "Red");

	const auto& materialGrey = std::make_shared<DefaultMaterial>();
	materialGrey->Texture = ResourceManager::GetWhiteTexture();
	materialGrey->DiffuseColor = { .5f, .5f, .5f };
	materialGrey->AmbientColor = { .5f, .5f, .5f };
	materialGrey->SpecularColor = { .5f, .5f, .5f };
	materialGrey->Shininess = 30.0f;
	ResourceManager::LoadMaterial(materialGrey, "grey");

	const auto& materialBlue = std::make_shared<DefaultMaterial>();
	materialBlue->Texture = ResourceManager::GetWhiteTexture();
	materialBlue->DiffuseColor = { .25f, .1f, .95f };
	materialBlue->AmbientColor = { .25f, .1f, .95f };
	materialBlue->SpecularColor = { .25f, .1f, .95f };
	materialBlue->Shininess = 50.0f;
	ResourceManager::LoadMaterial(materialBlue, "Blue");

	const auto& materialMonkey = std::make_shared<DefaultMaterial>();
	materialMonkey->Texture = textureMonkey;
	materialMonkey->Shininess = 10.0f;
	ResourceManager::LoadMaterial(materialMonkey, "MaterialMonkey");

	// create Meshes
	const auto& meshCube1 = std::make_shared<Mesh>(ResourceManager::GetInstance().GetCube2VertexArray(), materialTextured);
	const auto& meshCube2 = std::make_shared<Mesh>(ResourceManager::GetInstance().GetMonkeyVertexArray(), materialMonkey);
	const auto& meshCube3 = std::make_shared<Mesh>(ResourceManager::GetInstance().GetCube2VertexArray(), materialRed);
	const auto& meshCube4 = std::make_shared<Mesh>(ResourceManager::GetInstance().GetCubeVertexArray(), materialBlue);
	
	//default mesh
	mMeshes.push_back(std::make_shared <Mesh>());
	mMeshes.push_back(meshCube1);
	mMeshes.push_back(meshCube2);
	mMeshes.push_back(meshCube3);
	mMeshes.push_back(meshCube4);
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
