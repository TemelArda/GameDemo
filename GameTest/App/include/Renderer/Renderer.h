#pragma once
#include "VertexArray.h"
#include <memory>
#include  "../Camera.h"

namespace Core_Renderer
{
class Renderer
{
public:

	Renderer() = default;

	~Renderer() = default;

	void BeginScene(const std::shared_ptr<Core::Camera>& camera) const;

	void Submit(const std::shared_ptr<VertexArray>& vao);

	void EndScene();

	static void PrintRenderAPI();
private:

};
}