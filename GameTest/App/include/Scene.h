#pragma once
#include <memory>
#include "ECS.h"
#include "../Systems/include/CircleRenderSystem.h"
//#include "../Systems/include/RectangleRenderSystem.h"
#include "../Systems/include/ControllerMovementSystem.h"

namespace Core
{

class Scene
{
public:
	Scene();
	
	~Scene() = default;

	void Initilize();

	void Update(float ts);

	void Render();

	void Shutdown();
private:
	std::shared_ptr<Core_ECS::Registry> mRegistry;

	std::shared_ptr<CircleRenderSystem> mCircleRenderSystem;

	//std::shared_ptr<RectangleRenderSystem> mRectangleRenderSystem;

	std::shared_ptr<ControllerMovementSystem> mControllerMovementSystem;

	void RegisterComponents();

	void RegisterSystems();

	void InitilizeEntities();
};

} // namespace Core