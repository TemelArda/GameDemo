#pragma once
#include <list>
#include "Math/Mat4x4.h"


namespace Core
{
	class Camera;
	class Material;
	class Mesh;
	class Scene;
	struct LightSource;
}

namespace Core_Renderer
{

class VertexArray;

class Renderer
{
private:
	struct RenderData
	{
		bool operator<(const RenderData& other);
		
		std::shared_ptr<VertexArray> VertexArray;
		
		std::shared_ptr<Core::Material> Material;
		
		Core_Math::Mat4x4 Transform;
	};

	struct SceneData
	{
		Core_Math::Mat4x4 ViewProjectionMatrix;
		
		std::vector<Core::LightSource> lightSources;
		
		float Time = 0;
	};
public:

	Renderer() = default;

	~Renderer() = default;

	void BeginScene(const std::weak_ptr<Core::Scene> scene) const;

	void Submit(const std::weak_ptr<Core::Mesh> mesh, const Core_Math::Mat4x4&& t = Core_Math::Mat4x4::Identity());

	void EndScene();

	static void PrintRenderAPI();
private:
	static SceneData* mSceneData;

	std::list<RenderData> mRenderSequence;
	
	void flush();
};
}