#include "stdafx.h"
#include "../include/ControllerMovementSystem.h"
#include "../../include/Components.h"
#include "../../app.h"

namespace Core
{

void ControllerMovementSystem::Update(float ts)
{
	for (Core_ECS::Entity e : mEntities)
	{
		Transform2DComponent& t = mComponentManager->GetComponent<Transform2DComponent>(e);
		MovementComponent& mover = mComponentManager->GetComponent<MovementComponent>(e);

		Core_Math::Vector2 force = { App::GetController().GetLeftThumbStickX() , 
			- App::GetController().GetLeftThumbStickY() };
		
		mover.acceleration += force;
		mover.acceleration *= ts;

		mover.velocity += mover.acceleration * mover.baseSpeed;
		mover.velocity *=  ts;

		t.position += mover.velocity;

		mover.velocity /= ts;
		mover.acceleration = {0, 0};
	}
}

} // namespace Core