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

private:
	static IRendererAPI* mAPI;
};
}