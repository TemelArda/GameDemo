#include "stdafx.h"
#include "../include/Application.h"
#include "../include/Scene.h"
#include "../include/Event/Event.h"
#include "../include/Renderer/BufferLayout.h"
#include "../include/Renderer/Renderer.h"
#include "../include/Settings.h"
#include "../include/CoreDefines.h"
#include "../include/ResourceManager.h"
#include <chrono>

namespace Core
{
void Application::Initilize()
{		
	if (!mScene)
		mScene = std::make_shared<Scene>();
	if (!mDispatcher)
		mDispatcher = std::make_unique<Dispatcher>(DemoEvent::GetStaticType());
	if (!mRenderer)
		mRenderer = std::make_unique<Core_Renderer::Renderer>();
	if(!mCamera)
		mCamera = std::make_shared<Camera>();

	mRenderer->PrintRenderAPI();
	
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
	Core_Math::Transform3D transform;
	auto current = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current - mStartTime);
	float sin = (std::sin(elapsed.count() * 0.0005f) + 1) * .5f;
	float cos = std::cos(elapsed.count() * 0.005f);
	float sin2 = std::sin(elapsed.count() * 0.0005f) * 2;
	mRenderer->BeginScene(*mCamera, (float) elapsed.count());	
	//transform.Rotate({ 0.0f, sin * 2 * PI, sin * 2 * PI });
	for (size_t i = 0; i < mMeshes.size(); ++i)
	{
		float x =  (float)i - (mMeshes.size() * 0.5f );
		transform.mPosition = { -x , 0.0f, 0.0f };
		mRenderer->Submit(mMeshes[i], transform.GetModelMatrix());
	}
	
	mRenderer->EndScene();

	//mScene->Render();
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
	// create Meshes
	const auto& meshCube = std::make_shared<Mesh>();
	const auto& texture = ResourceManager::LoadTexture("blue_eyes.bmp", "BlueEyes");
	const auto& material = std::make_shared<DefaultMaterial>();
	material->Texture = texture;
	meshCube->SetMaterial(material);
	ResourceManager::LoadMaterial(material, "BlueEyes");

	const auto& meshQuad = std::make_shared<Mesh>();
	const auto& materialRed = std::make_shared<DefaultMaterial>();
	materialRed->Texture = texture;
	materialRed->DiffuseColor = { .85f, .1f, .05f, 1.0f };
	meshQuad->SetMaterial(materialRed);
	meshQuad->SetVertexArray(ResourceManager::GetInstance().GetQuadVertexArray());
	ResourceManager::LoadMaterial(materialRed, "RedEyes");


	mMeshes.push_back(std::make_shared <Mesh>());
	mMeshes.push_back(meshCube);
	mMeshes.push_back(meshQuad);

	mStartTime = std::chrono::high_resolution_clock::now();
}

} // namespace Core
