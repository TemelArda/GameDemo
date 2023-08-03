#pragma once
#include "VertexArray.h"
#include  "../Camera.h"
#include "Shader.h"

namespace Core_Math
{
	class Mat4x4;
}

namespace Core_Renderer
{

class Renderer
{
public:

	Renderer() = default;

	~Renderer() = default;

	void BeginScene(const Core::Camera& camera) const;

	void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao);

	void EndScene();

	static void PrintRenderAPI();
private:

	struct SceneData
	{
		Core_Math::Mat4x4 ViewProjectionMatrix;
	};

	static SceneData* mSceneData;
};
}