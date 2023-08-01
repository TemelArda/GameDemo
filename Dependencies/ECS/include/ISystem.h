#pragma once
#include <unordered_set>
#include "Types.h"
#include "ComponentManager.hpp"

namespace Core_ECS
{
class ISystem
{
public:
	ISystem() = default;
	
	~ISystem() = default;

	void SetRequiredComponents(const std::initializer_list<ComponentID>& componentID)
	{
		for(ComponentID id : componentID)
		{
			mRequiredComponents.set(id);
		}
	}

	void EntityChanged(Entity entity, const BitSet& entityComponents)
	{
		if ((entityComponents & mRequiredComponents) == mRequiredComponents)
		{
			mEntities.insert(entity);
		}
		else
		{
			mEntities.erase(entity);
		}
	}

	void EntityDestroyed(Entity entity)
	{
		mEntities.erase(entity);
	}

	void SetID(SystemID id)
	{
		mSystemID = id;
	}

	const SystemID GetID() const
	{
		return mSystemID;
	}
	
	void SetComponentManager(ComponentManager* componentManager)
	{
		mComponentManager = componentManager;
	}

	virtual void Update(float dt) = 0;

	virtual void Render() = 0;

protected:
	std::unordered_set<Entity> mEntities;

	BitSet mRequiredComponents;

	SystemID mSystemID;

	ComponentManager* mComponentManager;
};

}