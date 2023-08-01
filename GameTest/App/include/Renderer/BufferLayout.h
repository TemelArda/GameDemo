#pragma once
#include <cstdint>
#include <vector>
#include <GL/glew.h>

namespace Core_Renderer
{
struct BufferElement
{
	uint32_t count;
	uint32_t type;
	char normalized;

	static uint32_t GetSizeOfType(uint32_t type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(float);
		case GL_UNSIGNED_INT: return sizeof(uint32_t);
		case GL_BYTE: return sizeof(char);
		}
		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout() = default;
	
	~BufferLayout() = default;

	void PushFloat(uint32_t count, bool normalized = false);

	void PushUInt(uint32_t count, bool normalized = false);

	void PushChar(uint32_t count, bool normalized = true);

	inline const std::vector<BufferElement>& GetElements() const { return mElements; };

	inline uint32_t GetStride() const { return mStride; };

private:
	std::vector<BufferElement> mElements;
	
	uint32_t mStride = 0;

	inline constexpr static char NORMILIZE_MODE[] = { GL_FALSE, GL_TRUE };
};
} // namespace Core_Renderer