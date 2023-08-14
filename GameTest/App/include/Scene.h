#pragma once
#include <memory>
#include "Math/Vector3.h"
#include <vector>
#include <chrono>

namespace Core_ECS
{
class Registry;
}

namespace Core
{

struct LightSource
{
	Core_Math::Vector3 Position;
	Core_Math::Vector3 Color;
	float Intensity;
};

class Camera;

class Scene
{
public:
	Scene(std::shared_ptr<Core_ECS::Registry> registry);
	
	~Scene() = default;

	void Initilize();

	void Update(float ts);

	void Render();

	void Shutdown();

	std::shared_ptr<Core_ECS::Registry> GetRegistry() const { return mRegistry; }

	const std::shared_ptr<Camera> GetCamera() const { return mCamera; } 

	const std::vector<LightSource>& GetLightSources() const { return mLightSources; }

	const float GetElapsedTimeInSeconds() const;
private:
	std::shared_ptr<Core_ECS::Registry> mRegistry;

	std::shared_ptr<Camera> mCamera;

	std::vector<LightSource> mLightSources;

	std::chrono::steady_clock::time_point mStartTime;

	void InitilizeEntities();
};

} // namespace Core