#include "stdafx.h"
#include "../include/Scene.h"
#include "../include/Components.h"
#include "../include/Settings.h"
#include "ECS.h"
#include "../include/Camera.h"

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
	InitilizeEntities();
}

void Scene::Update(float ts)
{

}

void Scene::Render()
{

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

void Scene::Shutdown()
{
	LOG_INFO("Scene Destroyed");
}



void Scene::InitilizeEntities()
{
	Core_ECS::Entity player = mRegistry->CreateEntity();
	Transform2DComponent playerTransform(APP_INIT_WINDOW_WIDTH / 2, APP_INIT_WINDOW_HEIGHT / 2, .25, 0);

	CircleRendererComponent cir;
	cir.color = {.2f, .2f, .7f};
	cir.radius = .5f;
	cir.isFilled = TRUE;


	RectangleRendererComponent rect;
	rect.isFilled = false;
	rect.lineWidth = 5.0f;

	MovementComponent mover;

	mRegistry->AddComponent<Transform2DComponent>(player, playerTransform);
	mRegistry->AddComponent<CircleRendererComponent>(player, cir);
	mRegistry->AddComponent<MovementComponent>(player, mover);
	
}
}// namespace Core 
