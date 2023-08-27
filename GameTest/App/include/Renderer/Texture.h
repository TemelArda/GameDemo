#pragma once
#include <string>


namespace Core_Renderer
{
class Texture
{
public:
	Texture(const std::string& path);

	Texture(const void* data, uint32_t width, uint32_t height);

	Texture() = default;

	~Texture();
	
	void Bind(uint32_t slot = 0) const;

	void Unbind() const;

	const inline uint32_t GetID() const { return mRendererID; }

	const inline int GetWidth() const { return mWidth; }

	const inline int GetHeight() const { return mHeight; }

private:
	
	std::string mFilePath;
	
	uint32_t mRendererID{0};
	
	uint32_t mWidth{0};

	uint32_t mHeight{0};
};
} // namespace Core_Renderer