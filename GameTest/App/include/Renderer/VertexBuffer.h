#pragma once
#include <cstdint>


namespace Core_Renderer
{
using VertexBufferID = uint32_t;
class VertexBuffer
{
public:
	VertexBuffer(const void* data, const uint32_t size);

	~VertexBuffer();

	void Bind() const;

	void Unbind() const;

	const inline VertexBufferID GetID() const { return mRendererID; }
private:
	VertexBufferID mRendererID;
};
}