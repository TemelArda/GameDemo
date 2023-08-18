#pragma once
#include "Types.h"
#include "ISystem.h"
#include <unordered_map>
#include <memory>

namespace Core_ECS
{
class SystemManager
{
public:
	SystemManager() = default;
	
	~SystemManager();

	const SystemID RegisterSystem(std::shared_ptr<ISystem> system, std::initializer_list<ComponentID> componentIDs);

	void EntityDestroyed(Entity entity);

	void EntityChanged(Entity entity, const BitSet& entitySignature);

	std::shared_ptr<ISystem> GetSystem(SystemID systemID) const { return mSystems.at(systemID); }
private:
	std::unordered_map<SystemID, std::shared_ptr<ISystem>> mSystems;
	
	SystemID mNextSystemID {0};
};
}