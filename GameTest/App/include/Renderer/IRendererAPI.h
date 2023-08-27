#pragma once
#include <memory>
#include "Math/Vector4.h"
#include "VertexArray.h"

namespace Core_Renderer
{

class IRendererAPI
{
public:
	using ProgramID = uint32_t;

	using TextureID = uint32_t;
		
	IRendererAPI() = default;

	~IRendererAPI() = default;

	virtual void Clear() const = 0;

	virtual void SetClearColor(const Core_Math::Vector4& color) const = 0;

	virtual void DrawIndexed(const std::shared_ptr<Core_Renderer::VertexArray>& vao) const = 0;

	virtual void EnableDepthTest() const = 0;

	virtual void DisableDepthTest() const = 0;

	virtual void PrintRenderAPI() const = 0;

	virtual void EnableBlend() const = 0;

	virtual void DisableBlend() const = 0;

	virtual void BindProgram(ProgramID id) const = 0;

	virtual void BindTexture(TextureID id, uint32_t slot = 0) const =0;

	virtual void BindCubemap(TextureID id, uint32_t slot = 0) const = 0;
};
}
