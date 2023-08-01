#pragma once
#include <memory>
#include "Event/Dispatcher.h"
#include "Renderer/Shader.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"
#include <chrono>

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
	
	std::unique_ptr<Core_Renderer::Shader> mShader;

	std::unique_ptr<Core_Renderer::IndexBuffer> mIbo;

	std::unique_ptr<Core_Renderer::VertexBuffer> mVbo;

	std::unique_ptr<Core_Renderer::VertexArray> mVao;

	std::unique_ptr<Core_Renderer::Texture> mTexture;

	std::unique_ptr<Dispatcher> mDispatcher;
	
	
	Application() = default;
	
	~Application() = default;

	std::chrono::time_point<std::chrono::steady_clock> mStartTime;
};


}