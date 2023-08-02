#include "stdafx.h"
#include "../../include/Renderer/OpenGLRendererAPI.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Logger.h"

namespace Core_Renderer
{
void OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::SetClearColor(const Core_Math::Vector4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<Core_Renderer::VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::PrintRenderAPI()
{
	LOG_INFO("Open GL info: ");
	LOG_INFO("	Version: {}", (char*)glGetString(GL_VERSION));
	LOG_INFO("	Vendor: {}", (char*)glGetString(GL_VENDOR));
	LOG_INFO("	Renderer: {}", (char*)glGetString(GL_RENDERER));
}

}
