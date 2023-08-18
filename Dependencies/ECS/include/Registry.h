#pragma once
#include "Types.h"
#include "ComponentManager.hpp"
#include "EntityManager.h"
#include <memory>
#include "SystemManager.h"

namespace Core_ECS
{

class Registry
{
public:
	Registry() = default;

	~Registry() = default;

	template<typename component>
	void RegisterComponentType();

	template<typename component>
	void AddComponent(Entity entity, const component& c);
	
	template<typename component>
	void RemoveComponent(Entity entity);

	template<typename component>
	ComponentID GetComponentTypeId();

	template<typename component>
	component& GetComponent(Entity entity);

	Entity CreateEntity(){ return mEntityManager->CreateEntity(); }

	void DestroyEntity(Entity entity);

	const SystemID RegisterSystem(std::shared_ptr<ISystem> system, std::initializer_list<ComponentID> componentIDs);

	std::shared_ptr<ISystem> GetSystem(SystemID system){return mSystemManager->GetSystem(system); }

	void Initilize();

	void Shutdown();
private:
	std::shared_ptr<ComponentManager> mComponentManager;
	
	std::shared_ptr<EntityManager> mEntityManager;

	std::shared_ptr<SystemManager> mSystemManager;
};

template<typename component>
inline void Registry::RegisterComponentType()
{
	mComponentManager->RegisterComponentType<component>();
}

template<typename component>
inline void Registry::AddComponent(Entity entity, const component& c)
{
	ComponentID id = mComponentManager->GetComponentTypeID<component>();
	if (id == MAX_UINT32)
	{
		LOG_WARNING("Component type not registered");
		return;
	}
	mComponentManager->AddComponent<component>(entity, c);
	mEntityManager->SetEntityBit(entity, id);
	mSystemManager->EntityChanged(entity, mEntityManager->GetEntityBitSet(entity));
}

template<typename component>
inline void Registry::RemoveComponent(Entity entity)
{
	ComponentID id = mComponentManager->GetComponentTypeID<component>();
	if (id == MAX_UINT32)
	{
		LOG_WARNING("Component type not registered");
		return;
	}
	mComponentManager->RemoveComponent<component>(entity);
	mEntityManager->UnsetEntityBit(entity, id);
	mSystemManager->EntityChanged(entity, mEntityManager->GetEntityBitSet(entity));
}

template<typename component>
inline ComponentID Registry::GetComponentTypeId()
{
	return mComponentManager->GetComponentTypeID<component>();
}

template<typename component>
inline component& Registry::GetComponent(Entity entity)
{
	return mComponentManager->GetComponent<component>(entity);
}

}
