#include "../include/EntityManager.h"
#include "Logger.h"

namespace Core_ECS
{

EntityManager::EntityManager()
	:mNumberOfEntities(0)
{
	 //ctor
	for (Entity i = 0; i < MAX_ENTITIES; ++i)
	{	
		mAvailableEntities.push_back(i);
	}
}

Entity EntityManager::CreateEntity()
{
	if (mNumberOfEntities >= MAX_ENTITIES)
	{
		LOG_ERROR("Maximum number of entities reached, MAX_ENTITIES: {}", MAX_ENTITIES);
	}
	Entity entity = mAvailableEntities.front();
	mAvailableEntities.pop_front();
	return entity;
}

bool EntityManager::IsAlive(Entity entity) const
{
	if (entity >= MAX_ENTITIES)
		return false;

	for (auto it = mAvailableEntities.cbegin(); it != mAvailableEntities.cend(); ++it)
	{
		if (entity == *it)
			return false;
	}

	return true;
}

void EntityManager::DestroyEntity(Entity entity)
{	
	if(!IsAlive(entity))
	{
		LOG_ERROR("Entity {} is already dead", entity);
		return;
	}
	mEntityBitsets[entity].reset();
	mAvailableEntities.push_back(entity);
	--mNumberOfEntities;

}

void EntityManager::SetEntityBit(Entity entity, ComponentID component)
{
	if (!IsAlive(entity) || component >= MAX_COMPONENTS)
		return;

	mEntityBitsets[entity].set(component);
}

void EntityManager::UnsetEntityBit(Entity entity, ComponentID component)
{
	if (!IsAlive(entity) || component >= MAX_COMPONENTS)
		return;

	BitSet bitSet = mEntityBitsets[entity];
	bitSet.reset(component);
}

void EntityManager::SetEntityBitSet(Entity entity, const BitSet& bitSet)
{
	if (IsAlive(entity))
		mEntityBitsets[entity] = bitSet;
}

const BitSet& EntityManager::GetEntityBitSet(Entity entity) const
{
	if (IsAlive(entity))
		return mEntityBitsets[entity];
	BitSet bitSet;
	bitSet.reset();
	return bitSet;
}


}// namespace Core_ECS