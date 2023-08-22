#include "stdafx.h"
#include "../../include/System/PhysicsWorld.h"
#include "../../include/Components.h"
#include "Logger.h"
namespace
{
constexpr float GRAVITY_FORCE{ 9.82f };
}

namespace Core
{

void PhysicsWorld::Update(float dt)
{
	for(Core_ECS::Entity e : mEntities)
	{
		auto& rigidBodyComponent = mComponentManager->GetComponent<RigidBodyComponent>(e);
		if(rigidBodyComponent.IsKinematic)
			continue;

		auto& transformComponent = mComponentManager->GetComponent<TransformComponent>(e).transform;
		
		ApplyGravity(&rigidBodyComponent);
		const auto drag = rigidBodyComponent.Velocity.GetNormalized() * (rigidBodyComponent.Drag * -1);
		ApplyForce(&rigidBodyComponent, drag);

		float deltaTime = dt * 0.125f;

		rigidBodyComponent.Velocity += rigidBodyComponent.Acceleration * deltaTime;
		transformComponent.mPosition += rigidBodyComponent.Velocity * deltaTime;

		LOG_INFO("Velocity: {0}", rigidBodyComponent.Velocity.toString());
		LOG_INFO("Position: {0}", transformComponent.mPosition.toString());
		LOG_INFO("DT: {0}", deltaTime);

		rigidBodyComponent.Acceleration.SetToZero();
	}
}

void PhysicsWorld::Render()
{
return;
}
void PhysicsWorld::ApplyForce(RigidBodyComponent* rb, const Core_Math::Vector3& force) const
{
	rb->Acceleration += force / rb->Mass;

}
void PhysicsWorld::ApplyGravity(RigidBodyComponent* rb) const
{
	rb->Acceleration.y -= (GRAVITY_FORCE  / rb->Mass) * (rb->UseGravity);
}
}
