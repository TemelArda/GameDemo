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

struct SceneObject
{
	bool operator<(const SceneObject& other);
	
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

	void SubmitAABBObject(Core_Math::Mat4x4&& t = Core_Math::Mat4x4::Identity());

	void EndScene();

	void inline Renderer::SetAABBDebugMesh(const std::shared_ptr<Core::Mesh> mesh)
	{
		mAABBMesh = mesh;
	}

	static void PrintRenderAPI();
private:
	static SceneData* mSceneData;

	std::list<SceneObject> mRenderSequence;

	std::list<Core_Math::Mat4x4> mAABBObjectTransform;

	std::shared_ptr<Core::Mesh> mAABBMesh;
	
	void flush();

	void flushAABBObjects();
};
}