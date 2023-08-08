#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Math/Mat4x4.h"
#include "Math/Vector3.h"
#include "../Mesh.h"

namespace Core
{
	class Camera;
}

namespace Core_Renderer
{

class Renderer
{
public:

	Renderer() = default;

	~Renderer() = default;

	void BeginScene(const Core::Camera& camera, float Time) const;

	void Submit(const std::shared_ptr<Core::Mesh>& Mesh, const Core_Math::Mat4x4& t = Core_Math::Mat4x4::Identity());

	void EndScene();

	static void PrintRenderAPI();
private:

	struct SceneData
	{
		Core_Math::Mat4x4 ViewProjectionMatrix;
		Core_Math::Vector3 LightPosition;
		float Time;
	};

	static SceneData* mSceneData;
};
}