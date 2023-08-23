#include "stdafx.h"
#include "../../include/Renderer/Renderer.h"
#include "../../include/Renderer/RenderCommand.h"
#include "../../include/Scene.h"
#include "../../include/Materials/Material.h"
#include "../../include/Mesh.h"
#include "../../include/Camera.h" 
#include "../../include/Renderer/VertexArray.h"
#include "../../include//Renderer/Shader.h"
#include "Logger.h"


namespace
{
	constexpr const auto MAX_UINT32 { std::numeric_limits<uint32_t>::max() };
}

namespace Core_Renderer
{
 
Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData;



void Renderer::BeginScene(const std::weak_ptr<Core::Scene> scene) const
{
	const auto scenePtr = scene.lock();
	
	if (!scenePtr)
	{
		LOG_ERROR("Scene is nullptr");
		return;
	}

	mSceneData->ViewProjectionMatrix = scenePtr->GetCamera()->GetViewProjection();
	mSceneData->lightSources = scenePtr->GetLightSources();
	mSceneData->Time = scenePtr->GetElapsedTimeInSeconds();
	
	RenderCommand::EnableDepthTest();
	RenderCommand::EnableBlend();
}

void Renderer::Submit(const std::weak_ptr<Core::Mesh> mesh, const Core_Math::Mat4x4&& t)
{
	const auto meshPtr = mesh.lock();
	if (!meshPtr)
	{
		LOG_ERROR("Mesh is nullptr");
		return;
	}
	const auto vao = meshPtr->GetVertexArray();
	const auto material = meshPtr->GetMaterial();

	mRenderSequence.push_back({ vao, material, t });
}

void Renderer::SubmitAABBObject(Core_Math::Mat4x4&& t)
{
	mAABBObjectTransform.emplace_back(std::move(t));
}

void Renderer::EndScene()
{
	flush();	
	flushAABBObjects();
}

void Renderer::flush()
{
	
	mRenderSequence.sort();
	
	ShaderID currentShader = MAX_UINT32;
	Core::MaterialID currentMaterial = MAX_UINT32;
	VertexArrayID currentVAO = MAX_UINT32;
	
	while(!mRenderSequence.empty())
	{
		const auto& data = mRenderSequence.front();
		if (data.Material->GetShaderID() != currentShader)
		{
			const auto& shader = data.Material->GetShader();
			//shader->SetUniform3f("u_LightPosition", mSceneData->LightPosition);
			shader->Bind();
			shader->SetUniformMat4f("u_VP", mSceneData->ViewProjectionMatrix);
			//shader->SetUniform1f("u_Time", mSceneData->Time);
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
			data.VertexArray->GetIndexBuffer()->Bind();
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

void Renderer::flushAABBObjects()
{
	if (mAABBObjectTransform.empty() || !mAABBMesh)
		return;
	const auto& shader = mAABBMesh->GetMaterial()->GetShader();
	const auto& vao = mAABBMesh->GetVertexArray();

	shader->Bind();
	shader->SetUniformMat4f("u_VP", mSceneData->ViewProjectionMatrix);
	vao->Bind();
	vao->GetIndexBuffer()->Bind();
	
	while(!mAABBObjectTransform.empty())
	{
		const auto& transform = mAABBObjectTransform.front();

		shader->SetUniformMat4f("u_Transform", transform);
		RenderCommand::DrawIndexed(vao);
		mRenderSequence.pop_front();
	}

	shader->Unbind();
	vao->Unbind();
	vao->GetIndexBuffer()->Unbind();
}


void Renderer::PrintRenderAPI()
{
	RenderCommand::PrintRenderAPI();
}

bool Renderer::SceneObject::operator<(const SceneObject& other)
{

	
	if (VertexArray->GetID() < other.VertexArray->GetID())
		return true;
	else if (VertexArray->GetID() > other.VertexArray->GetID())
		return false;
	else
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
		}
	}
	return false;
}
}
