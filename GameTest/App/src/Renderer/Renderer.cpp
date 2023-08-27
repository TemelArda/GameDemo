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



void Renderer::InitilizeSkyBox(std::shared_ptr<Core::Mesh>& mesh)
{
	mSkyBoxMesh = std::move(mesh);
}

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
	DrawSkyBox();
	//flushAABBObjects();
	//flush();	
}

void Renderer::DrawSkyBox() const
{
	if (!mSkyBoxMesh)
	{
		LOG_ERROR("SkyBox mesh is nullptr");
		return;
	}
	RenderCommand::DisableDepthTest();

	const auto& skyBoxMat = mSkyBoxMesh->GetMaterial();
	const auto& skyBoxVAO = mSkyBoxMesh->GetVertexArray();
	
	RenderCommand::BindProgram(skyBoxMat->GetShaderID());
	skyBoxMat->SetUniforms();
	SetUniformMat4f(skyBoxMat->GetShaderID(), "u_VP", mSceneData->ViewProjectionMatrix);
	skyBoxVAO->Bind();
	skyBoxVAO->GetIndexBuffer()->Bind();
	RenderCommand::DrawIndexed(skyBoxVAO);
	
	RenderCommand::BindProgram(0);
	RenderCommand::BindCubemap(0);

	RenderCommand::EnableDepthTest();
}

void Renderer::flush()
{
	
	//TODO: Sort using paralel execution
	//std::sort(mRenderSequence.begin(), mRenderSequence.end());
	mRenderSequence.sort();

	ProgramID currentShader = MAX_UINT32;
	Core::MaterialID currentMaterial = MAX_UINT32;
	VertexArrayID currentVAO = MAX_UINT32;
	
	while(!mRenderSequence.empty())
	{
		const auto& data = mRenderSequence.front();
		if (data.Material->GetShaderID() != currentShader)
		{
			currentShader = data.Material->GetShaderID();
			//shader->SetUniform3f("u_LightPosition", mSceneData->LightPosition);
			RenderCommand::BindProgram(currentShader);
			SetUniformMat4f(currentShader, "u_VP", mSceneData->ViewProjectionMatrix);
			//shader->SetUniform1f("u_Time", mSceneData->Time);
		}
		if (data.Material->GetMaterialID() != currentMaterial)
		{
			data.Material->SetUniforms();
			currentMaterial = data.Material->GetMaterialID();
		}
		if (data.VertexArray->GetID() != currentVAO)
		{
			data.VertexArray->Bind();
			data.VertexArray->GetIndexBuffer()->Bind();
			currentVAO = data.VertexArray->GetID();
		}
		
		SetUniformMat4f(currentShader, "u_Transform", data.Transform);
		RenderCommand::DrawIndexed(data.VertexArray);
		mRenderSequence.pop_front();
	}

	RenderCommand::BindProgram(0);
	RenderCommand::BindTexture(0);
}

void Renderer::flushAABBObjects()
{
	if (!mAABBMesh)
		return;
	const auto& aabbMat = mAABBMesh->GetMaterial();
	const auto& aabbVAO = mAABBMesh->GetVertexArray();

	RenderCommand::BindProgram(aabbMat->GetShaderID());
	mAABBMesh->GetMaterial()->SetUniforms();
	SetUniformMat4f(aabbMat->GetShaderID(), "u_VP", mSceneData->ViewProjectionMatrix);
	aabbVAO->Bind();
	aabbVAO->GetIndexBuffer()->Bind();
	
	while(!mAABBObjectTransform.empty())
	{
		const auto& transform = mAABBObjectTransform.front();

		SetUniformMat4f(aabbMat->GetShaderID(), "u_Transform", transform);
		RenderCommand::DrawIndexed(aabbVAO);
		mAABBObjectTransform.pop_front();
	}

	RenderCommand::BindProgram(0);
	aabbVAO->Unbind();
	aabbVAO->GetIndexBuffer()->Unbind();
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
