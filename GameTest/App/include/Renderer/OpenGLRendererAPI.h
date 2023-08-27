#pragma once
#include "IRendererAPI.h"

namespace Core_Renderer{
class OpenGLRendererAPI : public IRendererAPI
{
public:
	virtual void Clear() const override;

	virtual void SetClearColor(const Core_Math::Vector4& color) const override;

	virtual void DrawIndexed(const std::shared_ptr<Core_Renderer::VertexArray>& vao) const override;

	virtual void PrintRenderAPI() const override;

	virtual void EnableDepthTest() const override;

	virtual void DisableDepthTest() const override;

	virtual void EnableBlend() const  override;

	virtual void DisableBlend() const  override;

	virtual void BindProgram(ProgramID id) const  override;

	virtual void BindTexture(TextureID id, uint32_t slot) const  override;

	virtual void BindCubemap(TextureID id, uint32_t slot) const  override;
};
} // namespace Core_Renderer