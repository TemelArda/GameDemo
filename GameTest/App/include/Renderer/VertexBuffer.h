#pragma once
#include <cstdint>
#include "BufferLayout.h"
#include <memory>

namespace Core_Renderer
{
using VertexBufferID = uint32_t;
class VertexBuffer
{
public:
	VertexBuffer(float* data, const uint32_t size, const uint32_t NumberOfVertices);

	~VertexBuffer();

	void SetData(const void* data, const uint32_t size, const uint32_t NumberOfVertices);

	void SetLayout(const BufferLayout& layout);

	const BufferLayout& GetLayout() const;

	void Bind() const;

	void Unbind() const;

	const inline VertexBufferID GetID() const { return mRendererID; }

	const inline uint32_t GetNumberofVertices() const { return mNumberofVertices; }
private:
	VertexBufferID mRendererID;
	
	uint32_t mNumberofVertices;

	BufferLayout mLayout;

	std::unique_ptr<float> mData;
};

const inline BufferLayout& Core_Renderer::VertexBuffer::GetLayout() const
{
	return mLayout;
}

void inline Core_Renderer::VertexBuffer::SetLayout(const BufferLayout& layout)
{
	mLayout = layout;
}
}