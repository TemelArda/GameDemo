#include "stdafx.h"
#include "../../include/Renderer/OpenGLRendererAPI.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Logger.h"

namespace Core_Renderer
{
void OpenGLRendererAPI::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::SetClearColor(const Core_Math::Vector4& color) const
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<Core_Renderer::VertexArray>& vertexArray) const
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
 
void OpenGLRendererAPI::PrintRenderAPI() const
{
	LOG_INFO("Open GL info: ");
	LOG_INFO("	Version: {}", (char*)glGetString(GL_VERSION));
	LOG_INFO("	Vendor: {}", (char*)glGetString(GL_VENDOR));
	LOG_INFO("	Renderer: {}", (char*)glGetString(GL_RENDERER));
}

void OpenGLRendererAPI::EnableDepthTest() const
{
	glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::DisableDepthTest() const
{
	glDisable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::EnableBlend() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRendererAPI::DisableBlend() const
{
	glDisable(GL_BLEND);
}

void OpenGLRendererAPI::BindProgram(ProgramID id) const
{
	glUseProgram(id);
}

void OpenGLRendererAPI::BindTexture(TextureID id, uint32_t slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void OpenGLRendererAPI::BindCubemap(TextureID id, uint32_t slot) const
{
	glBindVertexArray(id);
}

} // namespace Core_Renderer
