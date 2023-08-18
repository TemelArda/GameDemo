#pragma once
#include "ECS.h"

namespace Core_Renderer
{
	class Renderer;
}

namespace Core
{
class MeshRendererSystem : public Core_ECS::ISystem
{
public:
	MeshRendererSystem(const std::shared_ptr<Core_Renderer::Renderer>& renderer);

	// Inherited via ISystem
	virtual void Update(float dt) override;
	
	virtual void Render() override;
private:
	std::shared_ptr<Core_Renderer::Renderer> mRenderer;

};
}