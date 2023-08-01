#include "stdafx.h"
#include "../../include/Renderer/Texture.h"
#include "../../include/Renderer/Constants.h"
#include "../../TextureLoader.h"
#include "Logger.h"
#include <GL/glew.h>



namespace Core_Renderer
{
Texture::Texture(const std::string& fileName)
	:mRendererID(0), mWidth(0), mHeight(0), mBitPPixel(0), mData(nullptr)
{
	mFilePath = PATH_TO_TEXTURES + fileName;
	mData = loadBMPRaw(mFilePath.c_str(), mWidth, mHeight, false);
	if(!mData)
	{
		LOG_ERROR("Failed to load texture {}", fileName);
		return;
	}
	mBitPPixel = 32;
	
	glGenTextures(1, &mRendererID);
	
	glBindTexture(GL_TEXTURE_2D, mRendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mData);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mRendererID);
	delete[] mData;
}

void Texture::Bind(uint32_t slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, mRendererID);
}
void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
}