#pragma once
#include "ECS.h"
#include "Math/Vector3.h"

namespace Core
{
struct RigidBodyComponent;

class PhysicsWorld: public Core_ECS::ISystem
{
public:
	virtual void Update(float dt) override;
	
	virtual void Render() override;

	void ApplyForce(RigidBodyComponent* rb, const Core_Math::Vector3& force) const;
private:

	void ApplyGravity(RigidBodyComponent* rb) const;
};
}