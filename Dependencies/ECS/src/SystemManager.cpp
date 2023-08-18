#include "../include/SystemManager.h"

namespace Core_ECS
{
SystemManager::~SystemManager()
{
	  mSystems.clear();
}

const SystemID SystemManager::RegisterSystem(std::shared_ptr<ISystem> system, std::initializer_list<ComponentID> componentIDs)
{
	system->SetID(mNextSystemID);
	system->SetRequiredComponents(componentIDs);
	mSystems[mNextSystemID++] = system;
	return mNextSystemID - 1;
}

void SystemManager::EntityDestroyed(Entity entity)
{
	for (auto const& [systemId, system] : mSystems)
	{
		system->EntityDestroyed(entity);
	}
}

void SystemManager::EntityChanged(Entity entity, const BitSet& entitySignature)
{
	for (auto const& [systemId, system] : mSystems)
	{
		system->EntityChanged(entity, entitySignature);
	}
}
}