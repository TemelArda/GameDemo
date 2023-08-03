#include "stdafx.h"
#include "../include/Scene.h"
#include "../include/Components.h"
#include "../include/Settings.h"


namespace Core
{
Scene::Scene()
{
	mRegistry = std::make_shared<Core_ECS::Registry>();
	mCircleRenderSystem = std::make_shared<CircleRenderSystem>();
	//mRectangleRenderSystem = std::make_shared<RectangleRenderSystem>();
	mControllerMovementSystem = std::make_shared<ControllerMovementSystem>();
}

void Scene::Initilize()
{
	mRegistry->Initilize();

	RegisterComponents();
	RegisterSystems();
	InitilizeEntities();
}

void Scene::Update(float ts)
{
	mControllerMovementSystem->Update(ts);
}

void Scene::Render()
{
	mCircleRenderSystem->Render();
	//mRectangleRenderSystem->Render();
}

void Scene::Shutdown()
{
	LOG_INFO("Scene Destroyed");
}

void Scene::RegisterComponents()
{
	mRegistry->RegisterComponentType<Transform2DComponent>();
	mRegistry->RegisterComponentType<CircleRendererComponent>();
	mRegistry->RegisterComponentType<RectangleRendererComponent>();
	mRegistry->RegisterComponentType<LineRendererComponent>();
	mRegistry->RegisterComponentType<MovementComponent>();
}

void Scene::RegisterSystems()
{
	const auto transform2DComponentID = mRegistry->GetComponentTypeId<Transform2DComponent>();
	const auto CircleComponentID = mRegistry->GetComponentTypeId<Transform2DComponent>();
	const auto RectangleComponentID = mRegistry->GetComponentTypeId<RectangleRendererComponent>();
	const auto MovementComponentID = mRegistry->GetComponentTypeId<MovementComponent>();
	
	mRegistry->RegisterSystem(mCircleRenderSystem, {transform2DComponentID, CircleComponentID});
	//mRegistry->RegisterSystem(mRectangleRenderSystem, {transform2DComponentID, RectangleComponentID});
	mRegistry->RegisterSystem(mControllerMovementSystem, {transform2DComponentID, MovementComponentID});
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
