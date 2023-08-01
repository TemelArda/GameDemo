#pragma once
#include "ECS.h"

namespace Core
{
	class LineRenderSystem : public Core_ECS::ISystem
	{
	public:
		LineRenderSystem() = default;

		~LineRenderSystem() = default;

		void Render() override;

		void Update(float ts) override
		{
			return;
		}

	private:
		void DrawLine(float x1, float y1, float x2, float y2);
	};
}
