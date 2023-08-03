#include "stdafx.h"
#include "../../include/Renderer/Renderer.h"
#include "Logger.h"
#include "../../include/Renderer/RenderCommand.h"
#include "../../include/Camera.h"
#include "Math/Mat4x4.h"


namespace Core_Renderer
{
 
Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData;

void Renderer::BeginScene(const Core::Camera& camera) const
{
	mSceneData->ViewProjectionMatrix = camera.GetViewProjection();
}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao)
{
	const auto& ib = vao->GetIndexBuffer();
	vao->Bind();
	ib->Bind();
	shader->Bind();
	shader->SetUniformMat4f("u_MVP", mSceneData->ViewProjectionMatrix);
	RenderCommand::DrawIndexed(vao);
	shader->Unbind();
}
void Renderer::EndScene()
{
}
void Renderer::PrintRenderAPI()
{
	RenderCommand::PrintRenderAPI();
}
}
