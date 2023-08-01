#include "stdafx.h"
#include "../../include/Renderer/BufferLayout.h"
#include <GL/glew.h>

namespace Core_Renderer
{
void BufferLayout::PushFloat(uint32_t count, bool normalized)
{
	mElements.push_back({count, GL_FLOAT, NORMILIZE_MODE[normalized]});
	mStride += count * sizeof(float);
}

void BufferLayout::PushUInt(uint32_t count, bool normalized)
{
	mElements.push_back({ count, GL_UNSIGNED_INT, NORMILIZE_MODE[normalized] });
	mStride += count * sizeof(uint32_t);
}

void BufferLayout::PushChar(uint32_t count, bool normalized)
{
	mElements.push_back({ count, GL_BYTE, NORMILIZE_MODE[normalized]});
	mStride += count * sizeof(char);
}


} // namespace Core_Renderer
