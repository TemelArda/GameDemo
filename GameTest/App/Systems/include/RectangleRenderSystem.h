#pragma once
#include "ECS.h"

namespace Core
{

class RectangleRenderSystem : public Core_ECS::ISystem
{
public:
	RectangleRenderSystem() = default;

	~RectangleRenderSystem() = default;

	void Render() override;

	void Update(float ts) override;
private:
	void DrawRectangle(float width , float height, bool isFilled);
}

inline void RectangleRenderSystem::Update(float ts)
{
	return;
}
} // namespace Core