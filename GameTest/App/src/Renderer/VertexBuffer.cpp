#include "stdafx.h"
#include "../../include/Renderer/VertexBuffer.h"
#include "Logger.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

namespace Core_Renderer
{
VertexBuffer::VertexBuffer(const void* data, const uint32_t size, const uint32_t NumberOfVertices)
{
	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	mNumberofVertices = NumberOfVertices;
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &mRendererID);
}
void VertexBuffer::SetData(const void* data, const uint32_t size, const uint32_t NumberOfVertices)
{
   glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	mNumberofVertices = NumberOfVertices;
}
void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}
void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}