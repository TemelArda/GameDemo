#include "stdafx.h"
#include "../include/Application.h"
#include "../include/Event/Event.h"
#include "../include/Renderer/Renderer.h"
#include "../include/Layers/GameLayer.h"
#include "../include/Layers/DebugLayer.h"
#include "../include/Components.h"
#include "../include/System/MeshRendererSystem.h"
#include "../include/System/PhysicsWorld.h"
#include "../include/ResourceManager.h"
#include "ECS.h"

namespace Core
{
void Application::Initilize()
{		
	if (!mDispatcher)
		mDispatcher = std::make_shared<Dispatcher>();
	if (!mRenderer)
		mRenderer = std::make_shared<Core_Renderer::Renderer>();
	if (!mRegistry)
		mRegistry = std::make_shared<Core_ECS::Registry>();
	
	ResourceManager::GetInstance().Initilize();
	
	const auto skyBoxMaterial = ResourceManager::GetInstance().GetMaterial("Skybox");
	const auto skyboxVA = ResourceManager::GetInstance().GetVertexArray("Skybox");

	if(skyBoxMaterial.has_value() && skyboxVA.has_value())
	{
		auto& skyBoxMesh = std::make_shared<Mesh>(
			skyboxVA.value(),
			skyBoxMaterial.value()
			);
		mRenderer->InitilizeSkyBox(skyBoxMesh);
	}

	mRenderer->PrintRenderAPI();
	
	mRegistry->Initilize();

	
	RegisterComponents();
	/// Registering Systems
	const auto& transformId = mRegistry->GetComponentTypeId<TransformComponent>();
	const auto& meshId = mRegistry->GetComponentTypeId<MeshComponent>();
	const auto& rigidBodyId = mRegistry->GetComponentTypeId<RigidBodyComponent>();
	
	const auto meshRendererSystem = std::make_shared<MeshRendererSystem>(mRenderer);
	mRegisteredSystems.insert(std::make_pair("MeshRenderSystem", mRegistry->RegisterSystem(meshRendererSystem, { transformId, meshId })));
	
	const auto physicsWorld = std::make_shared<PhysicsWorld>();
	mRegisteredSystems.insert(std::make_pair("PhysicsWorld", mRegistry->RegisterSystem(physicsWorld, { transformId, rigidBodyId })));
	/// End of Registering Systems

	// Initilize the layer stack with the game layer
	const auto debugLayer = std::make_shared<DebugLayer>(mRenderer, physicsWorld);
	PushLayer(debugLayer);
	
	const auto gameLayer = std::make_shared<GameLayer>(
		mRenderer,
		meshRendererSystem,
		physicsWorld,
		mRegistry);
	PushLayer(gameLayer);
	



	//Dispatcher workflow Example
	mDispatcher->Subscribe(BIND_LISTENER_FUNCTION(gameLayer, GameLayer::OnEvent), EventType::Default);
	mDispatcher->Dispatch(DemoEvent(10));
}
void Application::Update(float ts)
{
	for (auto& layer : mLayerStack)
		layer->OnUpdate(ts  / (float) 1000);
}
void Application::Render()
{
	for(auto& layer : mLayerStack)
		layer->OnRender();
}

void Application::Shutdown()
{
	for(auto& layer : mLayerStack)
		layer->OnDetach();
}

void Application::PushLayer(std::shared_ptr<Layer> layer)
{
	mLayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(std::shared_ptr<Layer> overlay)
{
	mLayerStack.PushOverlay(overlay);
	overlay->OnAttach();
}

void Application::PopLayer(std::shared_ptr<Layer> layer)
{
	mLayerStack.PopLayer(layer);
	layer->OnDetach();
}

void Application::PopOverlay(std::shared_ptr<Layer> overlay)
{
	mLayerStack.PopOverlay(overlay);
	overlay->OnDetach();
}

void Application::RegisterComponents()
{
	mRegistry->RegisterComponentType<TransformComponent>();;
	mRegistry->RegisterComponentType<MeshComponent>();
	mRegistry->RegisterComponentType<SpriteRendererComponent>();
	mRegistry->RegisterComponentType<RigidBodyComponent>();
	mRegistry->RegisterComponentType<ColliderComponent>();
}

void Application::RegisterSystems()
{
	
}

} // namespace Core
