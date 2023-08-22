#include "stdafx.h"
#include "../include/Scene.h"
#include "../include/Components.h"
#include "../include/Settings.h"
#include "../include/Camera.h"
#include "../include/ResourceManager.h"
#include "../include/Material.h"
#include "../include/Mesh.h"
#include "../include/CoreDefines.h"
#include "Math/Transform3D.h"
#include "ECS.h"

namespace Core
{
Scene::Scene(std::shared_ptr<Core_ECS::Registry> registery)
	: mRegistry(std::move(registery))
{
   mCamera = std::make_shared<Camera>();
}

void Scene::Initilize()
{
	mStartTime = std::chrono::high_resolution_clock::now();
	LOG_INFO("Creating the new Scene...");
	InitilizeResources();
	InitilizeEntities();
}

void Scene::Shutdown()
{
	LOG_INFO("Scene Destroyed");
}

const float Scene::GetElapsedTimeInSeconds() const
{ 
	auto current = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current - mStartTime);
	return (float) elapsed.count();

}

const float Scene::GetElapsedTimeInMilliSeconds() const
{
	auto current = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current - mStartTime);
	return (float)elapsed.count();

}

void Scene::InitilizeEntities()
{
	Core_ECS::Entity player = mRegistry->CreateEntity();
	TransformComponent playerTransform;
	playerTransform.transform.Translate({ 0.0f, 10.0f, 0.0f });
	mRegistry->AddComponent<TransformComponent>(player, playerTransform);
	

	MeshComponent playerMesh(
		ResourceManager::GetInstance().GetCube2VertexArray(), 
		ResourceManager::GetInstance().GetMaterial("BlueEyes")
		);
	mRegistry->AddComponent<MeshComponent>(player, playerMesh);

	RigidBodyComponent playerRigidBody;
	playerRigidBody.Mass = 1.0f;
	playerRigidBody.Drag = 1.0f;
	//playerRigidBody.UseGravity = false;
	mRegistry->AddComponent<RigidBodyComponent>(player, playerRigidBody);
}
void Scene::InitilizeResources()
{
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
	materialRed->DiffuseColor = { .85f, .1f, .05f };
	materialRed->AmbientColor = { .85f, .1f, .05f };
	materialRed->SpecularColor = { .85f, .1f, .05f };
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
}
}// namespace Core 
