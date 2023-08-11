#include "stdafx.h"
#include "../../include/Renderer/Renderer.h"
#include "Logger.h"
#include "../../include/Renderer/RenderCommand.h"
#include "../../include/Camera.h"
#include "../../include/Material.h"
#include "../../include/Mesh.h"


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
	const auto vao = Mesh->GetVertexArray();
	const auto material = Mesh->GetMaterial();

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

	mRenderSequence.push_back({ vao, material, t });
}
void Renderer::EndScene()
{
	flush();
	
}
void Renderer::PrintRenderAPI()
{
	RenderCommand::PrintRenderAPI();
}
void Renderer::flush()
{
	
	mRenderSequence.sort();
	
	ShaderID currentShader = mRenderSequence.front().Material->GetShaderID();
	Core::MaterialID currentMaterial = mRenderSequence.front().Material->GetMaterialID();
	VertexArrayID currentVAO = mRenderSequence.front().VertexArray->GetID();
	
	while(!mRenderSequence.empty())
	{
		const auto& data = mRenderSequence.front();
		if (data.Material->GetShaderID() != currentShader)
		{
			data.Material->Bind();
			const auto& shader = data.Material->GetShader();
			shader->SetUniform3f("u_LightPosition", mSceneData->LightPosition);
			shader->SetUniformMat4f("u_VP", mSceneData->ViewProjectionMatrix);
			shader->SetUniform1f("u_Time", mSceneData->Time);
			currentShader = shader->GetID();
		}
		if (data.Material->GetMaterialID() != currentMaterial)
		{
			data.Material->Bind();
			currentMaterial = data.Material->GetMaterialID();
		}
		if (data.VertexArray->GetID() != currentVAO)
		{
			data.VertexArray->Bind();
			currentVAO = data.VertexArray->GetID();
		}
		const auto & shader = data.Material->GetShader();
		
		shader->SetUniformMat4f("u_Transform", data.Transform);
		RenderCommand::DrawIndexed(data.VertexArray);
		
		if(mRenderSequence.size() == 1)
			data.Material->Unbind();
		mRenderSequence.pop_front();
	}
}

bool Renderer::RenderData::operator<(const RenderData& other)
{
	if (Material->GetShaderID() < other.Material->GetShaderID())
		return true;
	else if (Material->GetShaderID() > other.Material->GetShaderID())
		return false;
	else
	{
		if (Material->GetMaterialID() < other.Material->GetMaterialID())
			return true;
		else if (Material->GetMaterialID() > other.Material->GetMaterialID())
			return false;
		else
		{
			if (VertexArray->GetID() < other.VertexArray->GetID())
				return true;
			else if (VertexArray->GetID() > other.VertexArray->GetID())
				return false;
		}
	}
	return false;
}
}
