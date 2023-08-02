#pragma once
#include <cstdint>
#include <vector>
#include <GL/glew.h>
#include <initializer_list>

namespace Core_Renderer
{
enum class ShaderDataType
{
	None = 0,
	Float,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4,
	Int,
	Int2,
	Int3,
	Int4,
	Bool
};

static std::tuple<uint32_t, uint32_t> ShaderDataToSizeAndCount(ShaderDataType t)
{
	switch (t)
	{
	case ShaderDataType::None:
		return {0, 0};
		break;
	case ShaderDataType::Float:
		return {sizeof(float), 1};
		break;
	case ShaderDataType::Float2:
		return {sizeof(float) * 2, 2};
		break;
	case ShaderDataType::Float3:
		return {sizeof(float) * 3, 3};
		break;
	case ShaderDataType::Float4:
		return {sizeof(float) * 4, 4};
		break;
	case ShaderDataType::Mat3:
		return {sizeof(float) * 3 * 3, 3 * 3};
		break;
	case ShaderDataType::Mat4:
		return {sizeof(float) * 4 * 4, 4 * 4};
		break;
	case ShaderDataType::Int:
		return {sizeof(int), 1};
		break;
	case ShaderDataType::Int2:
		return {sizeof(int) * 2, 2};
		break;
	case ShaderDataType::Int3:
		return {sizeof(int) * 3, 3};
		break;
	case ShaderDataType::Int4:
		return {sizeof(int) * 4, 4};
		break;
	case ShaderDataType::Bool:
		return {sizeof(unsigned char), 1};
		break;
	default:
		break;
	}
	return {0, 0};
}

struct BufferElement
{
	BufferElement() = default;

	BufferElement(ShaderDataType type, const std::string name, bool normilized = false)
		: Name(name), Size(0), Type(type), Normilized(normilized), Offset(0), Count(0)
	{
		const auto [s, c] = ShaderDataToSizeAndCount(type);
		Size = s;
		Count = c;
	}
	
	std::string Name;
	
	ShaderDataType Type;
	
	uint32_t Size;
	
	uint32_t Offset;
	
	uint32_t Count;

	bool Normilized;
};

class BufferLayout
{
public:
	BufferLayout(const std::initializer_list<BufferElement>& elements);

	inline const std::vector<BufferElement>& GetElements() const { return mElements; };

	inline uint32_t GetStride() const { return mStride; };

	static uint32_t ShaderTypeToOpenGLType(const ShaderDataType& t);

	~BufferLayout() = default;
	BufferLayout() = default;

private:

	void CalculateOffsetAndStride();

	std::vector<BufferElement> mElements;
	
	uint32_t mStride = 0;

	inline constexpr static char NORMILIZE_MODE[] = { GL_FALSE, GL_TRUE };
};
} // namespace Core_Renderer