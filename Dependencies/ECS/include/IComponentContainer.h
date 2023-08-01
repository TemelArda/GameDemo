#pragma once

namespace Core_ECS
{
	class IComponentContainer
	{
 	public:
 		IComponentContainer() = default;
 		
		~IComponentContainer() = default;

		IComponentContainer(const IComponentContainer&) = delete;

		IComponentContainer& operator=(const IComponentContainer&) = delete;

		IComponentContainer(IComponentContainer&&) = delete;

		IComponentContainer& operator=(IComponentContainer&&) = delete;

		virtual bool EntityDestroyed(Entity entity) = 0;
 	};
 } // namespace Core_ECS