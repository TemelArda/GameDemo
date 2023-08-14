#pragma once
#include <cstdint>


namespace Core_Renderer
{
enum BufferDrawType
{
	STATIC_DRAW = 0x88E4, DYNAMIC_DRAW = 0x88E8, STREAM_DRAW = 0x88E0
};

class UniformBuffer
{
using UniforBufferID = uint32_t;
public:
	UniformBuffer(const void* data, const uint32_t size, BufferDrawType type);

	~UniformBuffer();

	void SetData(const void* data, const uint32_t offset, const uint32_t size);

	void Bind() const;
	
	void Unbind() const;

	const UniforBufferID GetBufferID() const {return mBufferID;}
private :
	UniforBufferID mBufferID;

};
}