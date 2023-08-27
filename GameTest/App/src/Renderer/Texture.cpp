#include "stdafx.h"
#include "../../include/Renderer/Texture.h"
#include "../../TextureLoader.h"
#include "Logger.h"
#include <GL/glew.h>



namespace Core_Renderer
{
Texture::Texture(const std::string& filePath)
{
	mFilePath = filePath;
	const unsigned char* data = loadBMPRaw(mFilePath.c_str(), mWidth, mHeight, false);
	if(!data)
	{
		LOG_ERROR("Failed to load texture {}", filePath);
		return;
	}
	
	glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);
	
	glBindTexture(GL_TEXTURE_2D, mRendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	delete [] data;
}

Texture::Texture(const void* data, uint32_t width, uint32_t height) :
mWidth(width), mHeight(height)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);

	glBindTexture(GL_TEXTURE_2D, mRendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

Texture::~Texture()
{
	glDeleteTextures(1, &mRendererID);
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