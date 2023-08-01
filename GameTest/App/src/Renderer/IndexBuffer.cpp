#include "stdafx.h"
#include "../../include/Renderer/IndexBuffer.h"
#include "Logger.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

namespace Core_Renderer
{
IndexBuffer::IndexBuffer(const uint32_t* indices, const uint32_t count) 
	: mCount(count)
{
	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &mRendererID);
}
void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}
void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}