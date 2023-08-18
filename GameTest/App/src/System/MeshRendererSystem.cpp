#include "stdafx.h"
#include "../../include/System/MeshRendererSystem.h"
#include "../../include/Components.h"
#include "../../include/Renderer/Renderer.h"
#include <memory>

namespace Core
{
MeshRendererSystem::MeshRendererSystem(const std::shared_ptr<Core_Renderer::Renderer>& renderer):
	mRenderer(renderer)
	{
	}

void MeshRendererSystem::Update(float dt)
{
	return;
}

void MeshRendererSystem::Render()
{
	for(Core_ECS::Entity e: mEntities)
	{
		auto& mesh = mComponentManager->GetComponent<MeshComponent>(e).mesh;
		auto& transform = mComponentManager->GetComponent<TransformComponent>(e).transform;
		mRenderer->Submit(mesh, transform.GetModelMatrix());
	}
}
}
