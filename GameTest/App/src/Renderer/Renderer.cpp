#include "stdafx.h"
#include "../../include/Renderer/Renderer.h"
#include "Logger.h"
#include <GL/glew.h>

namespace Core_Renderer
{
void Core_Renderer::Renderer::Render(const VertexArray* vao, const IndexBuffer* Ibo, const Shader* shader)
{
	vao->Bind();
	Ibo->Bind();
	shader->Bind();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glDrawElements(GL_TRIANGLES, Ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	shader->Unbind();
}
void Renderer::PrintOpenGLVersion()
{
	LOG_INFO("Open GL info: ");
	LOG_INFO("	Version: {}", (char*)glGetString(GL_VERSION));
	LOG_INFO("	Vendor: {}", (char*)glGetString(GL_VENDOR));
	LOG_INFO("	Renderer: {}", (char*)glGetString(GL_RENDERER));
}
}
