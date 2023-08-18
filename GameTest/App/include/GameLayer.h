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
class MeshRendererSystem;

class GameLayer: public Layer
{
public:
	GameLayer(std::shared_ptr<Core_Renderer::Renderer> renderer, 
		std::shared_ptr<MeshRendererSystem> meshRenderer, 
		std::shared_ptr<Core_ECS::Registry> reg);

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

	std::shared_ptr<MeshRendererSystem> mMeshRenderer;

	std::shared_ptr<Scene> mScene;
};
}