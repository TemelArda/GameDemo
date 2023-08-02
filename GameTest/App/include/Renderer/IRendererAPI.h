#pragma once
#include <memory>
#include "Math/Vector4.h"
#include "VertexArray.h"

namespace Core_Renderer
{

class IRendererAPI
{
public:
	IRendererAPI() = default;

	~IRendererAPI() = default;

	virtual void Clear() = 0;

	virtual void SetClearColor(const Core_Math::Vector4& color) = 0;

	virtual void DrawIndexed(const std::shared_ptr<Core_Renderer::VertexArray>& vao) = 0;

	virtual void PrintRenderAPI() = 0;

private:

};
}
