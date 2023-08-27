#pragma once
#include <memory>
#include "Math/Vector4.h"
#include "IRendererAPI.h"


namespace Core_Renderer
{
class RenderCommand
{
public:
	RenderCommand() = default;

	~RenderCommand() = default;

	static inline void Clear()
	{
		mAPI->Clear();
	}

	static inline void SetClearColor(const Core_Math::Vector4& color)
	{
		mAPI->SetClearColor(color);
	}

	static inline void DrawIndexed(const std::shared_ptr<Core_Renderer::VertexArray>& vao)
	{
		mAPI->DrawIndexed(vao);
	}
	static inline void PrintRenderAPI()
	{
		mAPI->PrintRenderAPI();
	}

	static inline void EnableDepthTest()
	{
		mAPI->EnableDepthTest();
	}

	static inline void DisableDepthTest()
	{
		mAPI->DisableDepthTest();
	}

	static inline void EnableBlend()
	{
		mAPI->EnableBlend();
	}

	static inline void DisableBlend()
	{
		mAPI->DisableBlend();
	}

	static inline void BindProgram(uint32_t id)
	{
		mAPI->BindProgram(id);
	}

	static inline void BindTexture(uint32_t id, uint32_t slot = 0)
	{
		mAPI->BindTexture(id, slot);
	}

	static inline void BindCubemap(uint32_t id, uint32_t slot = 0)
	{
		mAPI->BindCubemap(id, slot);
	}

private:
	static IRendererAPI* mAPI;
};
}