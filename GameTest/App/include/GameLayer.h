#pragma once
#include "Layer.h"
#include "Scene.h"
#include <memory>

namespace Core_Renderer
{
class Renderer;
}

namespace Core_ECS
{
class	Registry;
}

namespace Core
{

class Camera;

class Mesh;

class GameLayer: public Layer
{
public:
	GameLayer(std::shared_ptr<Core_Renderer::Renderer>, std::shared_ptr<Core_ECS::Registry> reg);

	virtual void OnAttach() override;
	
	virtual void OnDetach() override;
	
	virtual void OnUpdate(float ts) override;
	
	virtual void OnEvent(IEvent& e) override;
	
	virtual void OnRender() override;

	virtual void Enable() override;

	virtual void Disable() override;

	std::shared_ptr<Scene> GetActiveScene() const { return mScene; }

	void SetActiveScene(std::shared_ptr<Scene> scene) { mScene = scene; }

private:

	bool mIsEnabled;

	std::shared_ptr<Core_Renderer::Renderer> mRenderer;

	std::shared_ptr<Scene> mScene;

	std::vector<std::shared_ptr<Mesh>> mMeshes;

	std::shared_ptr<Camera> mCamera;
};
}