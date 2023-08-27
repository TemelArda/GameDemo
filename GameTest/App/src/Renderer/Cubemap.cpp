#include "stdafx.h"
#include "../../include/Renderer/Cubemap.h"
#include "../../TextureLoader.h"
#include "Logger.h"
#include <GL/glew.h>

namespace Core_Renderer
{
Cubemap::Cubemap(const CubeMapFilePath& filePaths)
{
	glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &mRendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mRendererID);

	if (!LoadCubemapFace(filePaths.Right, GL_TEXTURE_CUBE_MAP_POSITIVE_X))
	{
		LOG_ERROR("Failed to load cubemap face {}", filePaths.Right);
		return;
	}

	if (!LoadCubemapFace(filePaths.Left, GL_TEXTURE_CUBE_MAP_NEGATIVE_X))
	{
		LOG_ERROR("Failed to load cubemap face {}", filePaths.Left);
		return;
	}

	if (!LoadCubemapFace(filePaths.Top, GL_TEXTURE_CUBE_MAP_POSITIVE_Y))
	{
		LOG_ERROR("Failed to load cubemap face {}", filePaths.Top);
		return;
	}

	if (!LoadCubemapFace(filePaths.Bottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y))
	{
		LOG_ERROR("Failed to load cubemap face {}", filePaths.Bottom);
		return;
	}

	if (!LoadCubemapFace(filePaths.Front, GL_TEXTURE_CUBE_MAP_POSITIVE_Z))
	{
		LOG_ERROR("Failed to load cubemap face {}", filePaths.Front);
		return;
	}

	if (!LoadCubemapFace(filePaths.Back, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z))
	{
		LOG_ERROR("Failed to load cubemap face {}", filePaths.Back);
		return;
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
void Cubemap::Bind(uint32_t slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mRendererID);
}

void Cubemap::Unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

bool Cubemap::LoadCubemapFace(const std::string& filePath, const unsigned int face)
{
	const unsigned char* data = loadBMPRaw(filePath.c_str(), mWidth, mHeight);
	if (!data)
	{
		LOG_ERROR("Failed to load texture {}", filePath);
		delete[] data;
		return false;
	}
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexImage2D(face, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	delete[] data;
	return true;
}

} // namespace Core_Renderer