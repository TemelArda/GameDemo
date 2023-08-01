#pragma once
#include "VertexBuffer.h"
#include "BufferLayout.h"

namespace Core_Renderer
{
using VertexBufferID = uint32_t;
class VertexArray
{
public:
	VertexArray() ;
	
	~VertexArray();

	void AddVertexBuffer(const VertexBuffer& vb, const BufferLayout& layout ) const;

	void Bind() const;
	
	void Unbind() const;

private:
	VertexBufferID mRendererID;
};
} // namespace Core_Renderer