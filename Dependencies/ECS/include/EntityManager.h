#pragma once
#include "Types.h"
#include <deque>


namespace Core_ECS 
{

class EntityManager
{
public:
	EntityManager();

	~EntityManager() = default;

	EntityManager(const EntityManager& em) = delete;

	EntityManager& operator=(const EntityManager& em) = delete;

	Entity CreateEntity();

	void DestroyEntity(Entity entity);

	bool IsAlive(Entity entity) const;

	std::uint32_t GetNumberOfEntities() const {return mNumberOfEntities;};

	void SetEntityBit(Entity entity, ComponentID component);

	void UnsetEntityBit(Entity entity, ComponentID component);

	void SetEntityBitSet(Entity entity, const BitSet& bitSet);

	const BitSet& GetEntityBitSet(Entity entity) const;

private:
	std::deque<Entity> mAvailableEntities;
	
	std::uint32_t mNumberOfEntities;

	//Index of the entity in the array is the entity id
	std::array<BitSet, MAX_ENTITIES> mEntityBitsets;
};
} // namespace CoreECS
