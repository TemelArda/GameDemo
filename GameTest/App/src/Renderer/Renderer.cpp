#include "stdafx.h"
#include "../../include/Renderer/Renderer.h"
#include "Logger.h"
#include "../../include/Renderer/RenderCommand.h"
#include "../../include/Camera.h"

namespace Core_Renderer
{
void Renderer::BeginScene(const std::shared_ptr<Core::Camera>& camera) const
{
	RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	RenderCommand::Clear();
}

void Renderer::Submit(const std::shared_ptr<VertexArray>& vao)
{
	
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
