#include "stdafx.h"
#include "../../include/Renderer/BufferLayout.h"


namespace Core_Renderer
{

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
	: mElements(elements)
{
	CalculateOffsetAndStride();
}

void BufferLayout::CalculateOffsetAndStride()
{
	uint32_t offset = 0;
	mStride = 0;
	for (auto& element : mElements)
	{
		element.Offset = offset;
		offset += element.Size;
		mStride += element.Size;
	}
}

uint32_t BufferLayout::ShaderTypeToOpenGLType(const ShaderDataType& t)
{
	switch (t)
	{
		case ShaderDataType::Float:
			return GL_FLOAT;
			break;
		case ShaderDataType::Float2:
			return GL_FLOAT;
			break;
		case ShaderDataType::Float3:
			return GL_FLOAT;
			break;
		case ShaderDataType::Float4:
			return GL_FLOAT;
			break;
		case ShaderDataType::Mat3:
			return GL_FLOAT;
			break;
		case ShaderDataType::Mat4:
			return GL_FLOAT;
			break;
		case ShaderDataType::Int:
			return GL_INT;
			break;
		case ShaderDataType::Int2:
			return GL_INT;
			break;
		case ShaderDataType::Int3:
			return GL_INT;
			break;
		case ShaderDataType::Int4:
			return GL_INT;
			break;
		case ShaderDataType::Bool:
			return GL_BOOL;
			break;
	}
	return 0;
}

} // namespace Core_Renderer
