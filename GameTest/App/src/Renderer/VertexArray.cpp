#include "stdafx.h"
#include "../../include/Renderer/VertexArray.h"
#include <GL/glew.h>
#include "Logger.h"

namespace Core_Renderer
{
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &mRendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mRendererID);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vb)
{
	const auto& layout = vb->GetLayout();
	if (layout.GetElements().size() < 1)
	{
		LOG_ERROR("Vertex Buffer has no layout");
		return;
	}

	glBindVertexArray(mRendererID);
	vb->Bind();

	const auto& elements = layout.GetElements();
	for (uint32_t i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.Count, BufferLayout::ShaderTypeToOpenGLType(element.Type), 
			element.Normilized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
	}
	
	mVertexBuffers.push_back(vb);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
{
	glBindVertexArray(mRendererID);
	ib->Bind();
	mIndexBuffer = ib;
}

void VertexArray::Bind() const { glBindVertexArray(mRendererID); };

void VertexArray::Unbind() const { glBindVertexArray(0); };
} // namespace Core_Renderer
