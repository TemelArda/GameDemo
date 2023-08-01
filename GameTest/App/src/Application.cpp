#include "stdafx.h"
#include "../include/Application.h"
#include "../include/Scene.h"
#include "../include/Event/Event.h"
#include "../include/Renderer/BufferLayout.h"
#include "../include/Renderer/Renderer.h"
#include "../include/Settings.h"
#include "Logger.h"
#include "Math/MathUtils.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <chrono>

namespace Core
{
void Application::Initilize()
{	
	
	Core_Renderer::Renderer::PrintOpenGLVersion();	
	
	if (!mScene)
		mScene = std::make_shared<Scene>();
	if (!mDispatcher)
		mDispatcher = std::make_unique<Dispatcher>(DemoEvent::GetStaticType());

	mScene->Initilize();

	mDispatcher->Subscribe(std::bind(&Application::testFunction, this, std::placeholders::_1));

	mDispatcher->Dispatch(DemoEvent(10));
	mDispatcher->UnSubscribe(BIND_LISTENER_FUNCTION(Application::testFunction));
}
void Application::Update(float ts)
{
	mScene->Update(ts);
}
void Application::Render()
{
	auto current = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current - mStartTime);
	mTexture->Bind();
	mShader->Bind();
	mShader->SetUniform1f("u_Time", (float)elapsed.count() / 1000.0);

	Core_Renderer::Renderer::Render(mVao.get(), mIbo.get(), mShader.get());

	mScene->Render();
}
void Application::Shutdown()
{
	mScene->Shutdown();
}

void Application::testFunction(IEvent& e)
{
	if (e.GetType() != EventType::Default)
	{
		LOG_INFO("Event Dispatched with wrong type\n Event: { }", e.toString());
		return;
	}
	DemoEvent de = static_cast<DemoEvent&>(e);
	LOG_INFO("testFunction called with: {}" , de.GetVariable());
	
	//Generate vertex array object

	// Vertex buffer data 3d position and UV
	float vertexData[] = {
		-0.5f, -0.5f, 0.0f, 0.0, 0.0,// bot-left  
		 0.5f, -0.5f, 0.0f, 1.0, 0.0,// bot-right 
		 0.5f,  0.5f, 0.0f,  1.0, 1.0,// top-right   
		 -0.5f, 0.5f, 0.0f, 0.0, 1.0,// top-left 
	};

	//**
	//float vUvs[] = {
	//	0.0, 0.0, // bot-left  
	//	1.0, 0.0, // bot-right 
	//	1.0, 1.0,  // top-right   
	//	0.0, 1.0, // top-left 
	//};
	//***
	// index buffer data
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mVao = std::make_unique<Core_Renderer::VertexArray>();
	mVbo = std::make_unique<Core_Renderer::VertexBuffer>(vertexData, 5 * 4 * sizeof(float));

	Core_Renderer::BufferLayout layout;
	layout.PushFloat(3);
	layout.PushFloat(2);
	mVao->AddVertexBuffer(*mVbo, layout);
	
	mIbo = std::make_unique<Core_Renderer::IndexBuffer>(indices, 6);
	
	// create shader
	mShader = std::make_unique<Core_Renderer::Shader>("Default.shader");
	mShader->Bind();
	mShader->SetUniform1f("u_Time", 0.0f);
	mStartTime = std::chrono::high_resolution_clock::now();
	
	// create texture
	mTexture = std::make_unique<Core_Renderer::Texture>("blue_eyes.bmp");
	mTexture->Bind();
	mShader->SetUniform1i("u_Texture", 0);
	

	Core_Math::Mat4x4 ortho = Core_Math::Ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	mShader->SetUniformMat4f("u_MVP", ortho);
	
	// unbind everything
	mShader->Unbind();
	mVbo->Unbind();
	mIbo->Unbind();
	mVao->Unbind();
}

} // namespace Core
