#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <memory>

namespace Core_Renderer
{
using VertexArrayID = uint32_t;
class VertexArray
{
public:
	VertexArray();
	
	~VertexArray();

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vb);

	std::vector<std::shared_ptr<VertexBuffer>> inline GetVertexBuffers() const { return mVertexBuffers; }

	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib);

	std::shared_ptr<IndexBuffer> inline GetIndexBuffer() const { return mIndexBuffer; }

	void Bind() const;
	
	void Unbind() const;
	 
	const VertexArrayID GetID() const { return mRendererID; }

private:
	VertexArrayID mRendererID;

	std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;

	std::shared_ptr<IndexBuffer> mIndexBuffer;
};
} // namespace Core_Renderer