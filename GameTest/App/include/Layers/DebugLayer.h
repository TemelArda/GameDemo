#pragma once
#include "Layer.h"
#include <memory>

namespace Core_Renderer
{
	class Renderer;
}


namespace Core
{
	class MeshRendererSystem;
	class PhysicsWorld;

class DebugLayer : public Layer
{
public:
	DebugLayer(std::shared_ptr<Core_Renderer::Renderer> renderer,
		std::shared_ptr<PhysicsWorld> physicsWorld);

	virtual void OnAttach() override;

	virtual void OnDetach() override;

	virtual void OnUpdate(float ts) override;

	virtual void OnEvent(IEvent& e) override;

	virtual void OnRender() override;

	virtual void Enable() override;

	virtual void Disable() override;

private:

	bool mIsEnabled;

	std::shared_ptr<Core_Renderer::Renderer> mRenderer;

	std::shared_ptr<PhysicsWorld> mPhysicsWorld;
};
}