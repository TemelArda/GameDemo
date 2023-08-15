#include "stdafx.h"
#include "../include/Application.h"
#include "../include/Event/Event.h"
#include "../include/Renderer/Renderer.h"
#include "../include/GameLayer.h"
#include "../include/Components.h"
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
	

	mRenderer->PrintRenderAPI();
	
	mRegistry->Initilize();
	RegisterComponents();
	RegisterSystems();

	// Initilize the layer stack with the game layer
	const auto gameLayer = std::make_shared<GameLayer>(mRenderer, mRegistry);
	PushLayer(gameLayer);

	//Dispatcher workflow Example
	mDispatcher->Subscribe(BIND_LISTENER_FUNCTION(gameLayer, GameLayer::OnEvent), EventType::Default);
	mDispatcher->Dispatch(DemoEvent(10));
}
void Application::Update(float ts)
{
	for (auto& layer : mLayerStack)
		layer->OnUpdate(ts);
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
	mRegistry->RegisterComponentType<Transform2DComponent>();
	mRegistry->RegisterComponentType<CircleRendererComponent>();
	mRegistry->RegisterComponentType<RectangleRendererComponent>();
	mRegistry->RegisterComponentType<LineRendererComponent>();
	mRegistry->RegisterComponentType<MovementComponent>();
}

void Application::RegisterSystems()
{

}

} // namespace Core
