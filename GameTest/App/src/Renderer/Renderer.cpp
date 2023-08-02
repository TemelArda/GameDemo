#include "stdafx.h"
#include "../../include/Renderer/Renderer.h"
#include "Logger.h"
#include "../../include/Renderer/RenderCommand.h"

namespace Core_Renderer
{
void Renderer::BeginScene()
{
}

void Renderer::Submit(const std::shared_ptr<VertexArray>& vao)
{
	RenderCommand::SetClearColor({ 0.05f, 0.05f,  0.05f, 1.0f });
	RenderCommand::Clear();
	const auto& ib = vao->GetIndexBuffer();
	vao->Bind();
	ib->Bind();
	RenderCommand::DrawIndexed(vao);
}
void Renderer::EndScene()
{
}
void Renderer::PrintRenderAPI()
{
	RenderCommand::PrintRenderAPI();
}
}
