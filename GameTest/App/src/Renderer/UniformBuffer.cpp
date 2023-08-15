#include "stdafx.h"
#include "../../include/Renderer/UniformBuffer.h"
#include <GL/glew.h>
#include "Logger.h"

namespace Core_Renderer
{
UniformBuffer::UniformBuffer(const void* data, const uint32_t size, BufferDrawType type)
{
	glGenBuffers(1, &mBufferID);
	
	glBindBuffer(GL_UNIFORM_BUFFER, mBufferID);

	glBufferData(GL_UNIFORM_BUFFER, size, data, type);
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &mBufferID);
}

void UniformBuffer::SetData(const void* data, const uint32_t offset, const uint32_t size)
{
	glBindBuffer(GL_UNIFORM_BUFFER, mBufferID);

	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}
void UniformBuffer::Bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, mBufferID);
}
void UniformBuffer::Unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
} // namespace Core_Renderer	
	