#include "../include/Registry.h"
#include "Logger.h"


namespace Core_ECS
{
void Registry::Initilize()
{
	mEntityManager = std::make_shared<EntityManager>();
	mComponentManager = std::make_shared<ComponentManager>();
	mSystemManager = std::make_shared<SystemManager>();
}

void Registry::Shutdown()
{
	LOG_INFO("Closing the Registry");
}

void Registry::DestroyEntity(Entity entity)
{
	mEntityManager->DestroyEntity(entity);
	mComponentManager->DestroyEntity(entity);
	mSystemManager->EntityDestroyed(entity);
}

void Registry::RegisterSystem(std::shared_ptr<ISystem> system, std::initializer_list<ComponentID> componentIDs)
{
	system->SetComponentManager(mComponentManager.get());
	mSystemManager->RegisterSystem(system, componentIDs);
}
}// namespace Core_ECS