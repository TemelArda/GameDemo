#pragma once
#include <string>
#include "Texture.h"


namespace Core_Renderer
{

struct CubeMapFilePath
{
	std::string Right;
	std::string Left;
	std::string Top;
	std::string Bottom;
	std::string Front;
	std::string Back;
};
class Cubemap : public Texture
{
public:

Cubemap(const CubeMapFilePath& filePaths);

void Bind(uint32_t slot = 0) const;

void Unbind() const;

const inline uint32_t GetID() const { return mRendererID; }

const inline int GetWidth() const { return mWidth; }

const inline int GetHeight() const { return mHeight; }

private:

bool LoadCubemapFace(const std::string& filePath, const unsigned int face);

uint32_t mRendererID{ 0 };

uint32_t mWidth{ 0 };

uint32_t mHeight{ 0 };
};

}