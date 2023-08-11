#pragma once
#include "VertexArray.h"
#include "Math/Mat4x4.h"
#include "Math/Vector3.h"
#include <list>

namespace Core
{
	class Camera;
	class Material;
	class Mesh;
}

namespace Core_Renderer
{

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
		Core_Math::Vector3 LightPosition;
		float Time;
	};
public:

	Renderer() = default;

	~Renderer() = default;

	void BeginScene(const Core::Camera& camera, float Time) const;

	void Submit(const std::shared_ptr<Core::Mesh>& Mesh, const Core_Math::Mat4x4& t = Core_Math::Mat4x4::Identity());

	void EndScene();

	static void PrintRenderAPI();
private:
	void flush();
	static SceneData* mSceneData;
	std::list<RenderData> mRenderSequence;
};
}