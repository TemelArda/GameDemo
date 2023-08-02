#pragma once
#include "VertexArray.h"
#include <memory>

namespace Core_Renderer
{
class Renderer
{
public:

	Renderer() = default;

	~Renderer() = default;

	void BeginScene();

	void Submit(const std::shared_ptr<VertexArray>& vao);

	void EndScene();

	static void PrintRenderAPI();
private:

};
}