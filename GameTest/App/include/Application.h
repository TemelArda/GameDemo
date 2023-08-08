#pragma once
#include <memory>
#include "Event/Dispatcher.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"
#include "Camera.h"
#include <chrono>
#include "Mesh.h"

namespace Core
{
class Scene;

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

	void testFunction(IEvent& E);

private:
	std::shared_ptr<Scene> mScene;
	

	std::shared_ptr<Core_Renderer::VertexArray> mVao;

	std::unique_ptr<Core_Renderer::Renderer> mRenderer;
	
	std::shared_ptr<Camera> mCamera;

	std::unique_ptr<Dispatcher> mDispatcher;

	std::vector<std::shared_ptr<Mesh>> mMeshes;
	
	Application() = default;
	
	~Application() = default;

	std::chrono::time_point<std::chrono::steady_clock> mStartTime;
};


}