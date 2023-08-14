#pragma once
#include <memory>
#include "Event/Dispatcher.h"
#include "LayerStack.h"

namespace Core_ECS
{
class Registry;
}

namespace Core_Renderer
{
class Renderer;
}

namespace Core
{
class Application
{

public:
	static Application& GetInstance()
	{
		static Application instance;
		return instance;
	}

	void Initilize();

	void Update(float ts);

	void Render();

	void Shutdown();

	void PushLayer(std::shared_ptr<Layer> layer);

	void PushOverlay(std::shared_ptr<Layer> layer);

	void PopLayer(std::shared_ptr<Layer> layer);

	void PopOverlay(std::shared_ptr<Layer> layer);

private:
	
	LayerStack mLayerStack;

	std::shared_ptr<Core_Renderer::Renderer> mRenderer;

	std::shared_ptr<Dispatcher> mDispatcher;
	
	Application() = default;
	
	~Application() = default;

	std::shared_ptr<Core_ECS::Registry> mRegistry;

private:

	void RegisterSystems();

	void RegisterComponents();

};


}