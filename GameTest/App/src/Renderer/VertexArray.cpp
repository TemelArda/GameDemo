#include "stdafx.h"
#include "../../include/Renderer/VertexArray.h"
#include <GL/glew.h>


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

void VertexArray::AddVertexBuffer(const VertexBuffer& vb, const BufferLayout& layout) const
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	uint32_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * BufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const { glBindVertexArray(mRendererID); };

void VertexArray::Unbind() const { glBindVertexArray(0); };
} // namespace Core_Renderer
