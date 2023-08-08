#include "stdafx.h"
#include "../../include/Renderer/Renderer.h"
#include "Logger.h"
#include "../../include/Renderer/RenderCommand.h"
#include "../../include/Camera.h"


namespace Core_Renderer
{
 
Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData;

void Renderer::BeginScene(const Core::Camera& camera, float Time) const
{
	mSceneData->ViewProjectionMatrix = camera.GetViewProjection();
	mSceneData->LightPosition = {-5, -15, 0};
	mSceneData->Time = Time;
	RenderCommand::EnableDepthTest();
}

void Renderer::Submit(const std::shared_ptr<Core::Mesh>& Mesh, const Core_Math::Mat4x4& t )
{
	const auto& vao = Mesh->GetVertexArray();
	const auto& material = Mesh->GetMaterial();

	vao->Bind();
	vao->GetIndexBuffer()->Bind();
	material->Bind();
	const auto& shader = material->GetShader();
	shader->SetUniform3f("u_LightPosition", mSceneData->LightPosition);
	shader->SetUniformMat4f("u_VP", mSceneData->ViewProjectionMatrix);
	shader->SetUniform1f("u_Time", mSceneData->Time);
	shader->SetUniformMat4f("u_Transform", t);
	
	RenderCommand::DrawIndexed(vao);
	
	material->Unbind();
}
void Renderer::EndScene()
{
}
void Renderer::PrintRenderAPI()
{
	RenderCommand::PrintRenderAPI();
}
}
