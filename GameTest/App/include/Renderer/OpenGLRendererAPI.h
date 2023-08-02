#pragma once
#include "IRendererAPI.h"

namespace Core_Renderer{
class OpenGLRendererAPI : public IRendererAPI
{
public:
	virtual void Clear() override;

	virtual void SetClearColor(const Core_Math::Vector4& color) override;

	virtual void DrawIndexed(const std::shared_ptr<Core_Renderer::VertexArray>& vao) override;

	virtual void PrintRenderAPI() override;

};
} // namespace Core_Renderer