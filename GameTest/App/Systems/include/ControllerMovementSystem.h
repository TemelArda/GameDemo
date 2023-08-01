#pragma once
#include "ECS.h"


namespace Core
{
class ControllerMovementSystem : public Core_ECS::ISystem
{
public:
	ControllerMovementSystem () = default;
	
	~ControllerMovementSystem () = default;

	void Update(float ds) override;

	void Render() override
	{
		return;
	}

private:

};
}

