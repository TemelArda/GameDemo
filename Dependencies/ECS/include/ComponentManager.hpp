#pragma once
#include "ComponentContainer.hpp"
#include "Types.h"
#include <memory>
#include <unordered_map>
#include <optional>
#include "Logger.h"

namespace Core_ECS
{

class ComponentManager
{

public:
	ComponentManager() = default;

	~ComponentManager() = default;
	
	template <typename T>
	void RegisterComponentType();

	template<typename T>
	std::optional<std::shared_ptr<ComponentContainer<T>>> GetComponentArray();

	template <typename T>
	void AddComponent(Entity entity, const T& component);

	template <typename T>
	ComponentID GetComponentTypeID() const;

	template <typename T>
	void RemoveComponent(Entity entity);

	template <typename T>
	T& GetComponent(Entity entity);

	void DestroyEntity(Entity entity);
private:

	std::unordered_map<const char*, std::shared_ptr<IComponentContainer>> mComponentContainers;

	std::unordered_map<const char*, ComponentID > mComponentIdMap;

	ComponentID mNextComponentTypeID{ 0 };
};

template <typename T>
void ComponentManager::RegisterComponentType()
{
	const char* typeName = typeid(T).name();
	if (mComponentIdMap.find(typeName) != mComponentIdMap.end())
	{
		LOG_WARNING("Component type already registered");
		return;
	}
	mComponentIdMap.emplace(typeName, mNextComponentTypeID);
	mComponentContainers.emplace(typeName, std::make_shared<ComponentContainer<T>>());
	++mNextComponentTypeID;
	LOG_INFO("Registered Component Type: {0}, ID: {1}", typeName, mNextComponentTypeID - 1);
}

template<typename T>
std::optional<std::shared_ptr<ComponentContainer<T>>> ComponentManager::GetComponentArray()
{
	const char* typeName = typeid(T).name();

	if (mComponentIdMap.find(typeName) == mComponentIdMap.end())
	{
		LOG_WARNING("Component type not registered");
		return { };
	}
	return std::static_pointer_cast<ComponentContainer<T>>(mComponentContainers[typeName]);
}

template <typename T>
void ComponentManager::AddComponent(Entity entity, const T& component)
{
	const char* typeName = typeid(T).name();

	if (mComponentIdMap.find(typeName) == mComponentIdMap.end())
	{
		LOG_WARNING("Component type not registered");
		return;
	}
	auto c = std::static_pointer_cast<ComponentContainer<T>>(mComponentContainers[typeName]);
	c->AddComponentData(entity, component);
}

template<typename T>
ComponentID ComponentManager::GetComponentTypeID() const
{
	const char* typeName = typeid(T).name();
	if (mComponentIdMap.find(typeName) == mComponentIdMap.end())
	{
		LOG_WARNING("Component type not registered");
		return MAX_UINT32;
	}
	return mComponentIdMap.at(typeName);
}

template <typename T>
void ComponentManager::RemoveComponent(Entity entity)
{
	const char* typeName = typeid(T).name();
	if (mComponentIdMap.find(typeName) == mComponentIdMap.end())
	{
		LOG_WARNING("Component type not registered");
		return;
	}
	GetComponentArray<T>().value()->RemoveComponentData(entity);
}

template <typename T>
T& ComponentManager::GetComponent(Entity entity)
{
	const char* typeName = typeid(T).name();
	if (mComponentIdMap.find(typeName) == mComponentIdMap.end())
	{
		LOG_WARNING("Component type not registered");
		return T();
	}
	return GetComponentArray<T>().value()->GetComponent(entity);
}

}