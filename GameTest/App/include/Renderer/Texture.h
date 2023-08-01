#pragma once
#include <string>

namespace Core_Renderer
{

class Texture
{
public:
	Texture(const std::string& path);

	~Texture();

	void Bind(uint32_t slot = 0) const;

	void Unbind() const;

	const inline uint32_t GetID() const { return mRendererID; }

	const inline int GetWidth() const { return mWidth; }

	const inline int GetHeight() const { return mHeight; }

	const inline int GetBitPerPixel() const { return mBitPPixel; }
private:
	uint32_t mRendererID;
	
	std::string mFilePath;
	
	unsigned char* mData;

	uint32_t mWidth, mHeight, mBitPPixel;
};
} // namespace Core_Renderer