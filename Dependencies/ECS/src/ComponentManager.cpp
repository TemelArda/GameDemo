#include "../include/ComponentManager.hpp"

namespace Core_ECS
{
void ComponentManager::DestroyEntity(Entity entity)
{
	for (auto const& pair : mComponentContainers)
	{
		auto const& component = pair.second;
		component->EntityDestroyed(entity);
	}
}
};