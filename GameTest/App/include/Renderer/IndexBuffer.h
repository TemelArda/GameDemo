#pragma once
#include <cstdint>


namespace Core_Renderer
{
using IndexBufferID = uint32_t;
class IndexBuffer
{
public:
	IndexBuffer(const uint32_t *indices, const uint32_t count);

	~IndexBuffer();

	void Bind() const;

	void Unbind() const;

	const inline uint32_t GetCount() const { return mCount; }

	const inline IndexBufferID GetID() const { return mRendererID; }
private:
	IndexBufferID mRendererID;

	uint32_t mCount;
};
}