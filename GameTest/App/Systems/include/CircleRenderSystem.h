#pragma once
#include "ECS.h"

namespace Core
{
class CircleRenderSystem: public Core_ECS::ISystem
{
public:
	CircleRenderSystem() = default;

	~CircleRenderSystem() = default;

	void Render() override;
	
	void Update(float ts) override
	{
		return;
	}

private:
	void DrawCircle(float r, int num_segments, bool isFilled);
};
}
