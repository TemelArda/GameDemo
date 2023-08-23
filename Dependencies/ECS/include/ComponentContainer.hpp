#pragma once
#include "Types.h"
#include "IComponentContainer.h"
#include "Logger.h"

namespace
{
	constexpr uint32_t MAX_UINT32 = UINT_LEAST32_MAX;
}

namespace Core_ECS
{

template <typename Component>
class ComponentContainer : public IComponentContainer
{
public:
	ComponentContainer()
		: mEntityCount(0)
	{
		for (size_t i = 0; i < MAX_ENTITIES; ++i)
		{
			mEntityToIndex[i] = MAX_UINT32;
			mIndexToEntity[i] = MAX_UINT32;
		}
	}

	void AddComponentData(Entity entity, const Component& c);

	bool RemoveComponentData(Entity entity);

	Component& GetComponent(Entity entity);

	bool EntityDestroyed(Entity entity);

	std::array<Component, MAX_ENTITIES>& GetContainer(){ return mComponentContainer;}

	std::uint32_t GetEntityCount() const { return mEntityCount; }

private:
	
	std::array<Component, MAX_ENTITIES> mComponentContainer;

	std::array<uint32_t, MAX_ENTITIES> mEntityToIndex;

	std::array<uint32_t, MAX_ENTITIES> mIndexToEntity;

	std::uint32_t mEntityCount;
};

template<typename Component>
void ComponentContainer<Component>::AddComponentData(Entity entity, const Component& c)
{
	if (mEntityToIndex[entity] != MAX_UINT32)
	{
		auto type = typeid(Component).name();
		LOG_WARNING("Entity already has a component of type {}", type);
		return;
	}
	uint32_t index = mEntityCount;
	mEntityToIndex[entity] = index;
	mIndexToEntity[index] = entity;
	mComponentContainer[index] = c;
	++mEntityCount;
}

template<typename Component>
bool ComponentContainer<Component>::RemoveComponentData(Entity entity)
{
	uint32_t indexToRemove = mEntityToIndex[entity];
	if (indexToRemove == MAX_UINT32)
	{
		auto type = typeid(Component).name();
		LOG_WARNING("Entity don't have a component of type {}", type);
		return false;
	}
	uint32_t indexOfLastElement = mEntityCount - 1;
	if (mEntityCount > 1)
		mComponentContainer[indexToRemove] = mComponentContainer[indexOfLastElement];

	Entity entityOfLastElement = mIndexToEntity[indexOfLastElement];
	mEntityToIndex[entityOfLastElement] = indexToRemove;
	mIndexToEntity[indexToRemove] = entityOfLastElement;

	mIndexToEntity[indexOfLastElement] = MAX_UINT32;
	mEntityToIndex[entity] = MAX_UINT32;
	--mEntityCount;

	return true;
}

template<typename Component>
Component& ComponentContainer<Component>::GetComponent(Entity entity)
{
	uint32_t index = mEntityToIndex[entity];
	if (index == MAX_UINT32)
	{
		LOG_WARNING("CAN'T GET COMPONENT!\n Entity {} don't have a component {}", entity, typeid(Component).name());
		assert(false);
	}
	return mComponentContainer[index];
}

template<typename Component>
bool ComponentContainer<Component>::EntityDestroyed(Entity entity)
{
	uint32_t index = mEntityToIndex[entity];
	if (index == MAX_UINT32)
		return false;
	return RemoveComponentData(entity);
}
} // namespace Core_ECS	
