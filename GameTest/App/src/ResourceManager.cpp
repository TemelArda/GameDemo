#include "stdafx.h"
#include "../include/ResourceManager.h"
#include "../include/Resources.h"
#include "../include/Materials/DefaultMaterial.h"
#include "../include/Materials/SkyboxMaterial.h"
#include "../include/ModelLoader.h"
#include "../include/Renderer/Shader.h"
#include "../include/Renderer/Texture.h"
#include "../include/Renderer/VertexArray.h"
#include "../include/Renderer/Cubemap.h"
#include <assert.h>
#include <mutex>
#include <filesystem>


namespace
{
	constexpr auto CUBE_FILE_NAME{ "cube.obj" };
	constexpr auto SPHERE_FILE_NAME{ "sphere.obj" };
	constexpr auto MONKEY_FILE_NAME{ "monkey.obj" };
	constexpr auto BALB_FILE_NAME{ "balb.obj" };
} // namespace

static float vertexDataCube[] = {
	-0.5f, -0.5f, -0.5f, 0.0, 0.0, 1.0, 0.0, 0.0,// bot-left  front face
	 0.5f, -0.5f, -0.5f, 0.0, 0.0, 1.0, 1.0, 0.0,// bot-right front face
	 0.5f,  0.5f, -0.5f, 0.0, 0.0, 1.0, 1.0, 1.0,// top-right  front face
	 -0.5f, 0.5f, -0.5f, 0.0, 0.0, 1.0, 0.0, 1.0,// top-left front face

	 -0.5f, -0.5f, -0.5f, 1.0, 0.0, 0.0, 0.0, 0.0,// bot-left  right face
	 -0.5f, -0.5f, 0.5f, 1.0, 0.0, 0.0, 0.0, 0.0,// bot-right right face
	 -0.5f, 0.5f, 0.5f, 1.0, 0.0, 0.0, 0.0, 0.0,// top-right  right face
	 -0.5f, 0.5f, -0.5f, 1.0, 0.0, 0.0, 0.0, 0.0,// top-left right face

	 -0.5f, -0.5f, 0.5f, 0.0, 0.0, -1.0, 0.0, 0.0,// bot-left  back face
	 0.5f, -0.5f, 0.5f, 0.0, 0.0, -1.0, 0.0, 0.0,// bot-right back face
	 0.5f, 0.5f, 0.5f, 0.0, 0.0, -1.0, 0.0, 0.0,// top-right  back face
	 -0.5f, 0.5f, 0.5f, 0.0, 0.0, -1.0, 0.0, 0.0,// top-left back face

	 0.5f, -0.5f, -0.5f, -1.0, 0.0, 0.0, 0.0, 0.0,// bot-left  left face
	 0.5f, -0.5f, 0.5f, -1.0, 0.0, 0.0, 0.0, 0.0,// bot-right left face
	 0.5f, 0.5f, 0.5f, -1.0, 0.0, 0.0, 0.0, 0.0,// top-right  left face
	 0.5f, 0.5f, -0.5f, -1.0, 0.0, 0.0, 0.0, 0.0,// top-left left face

	 0.5f, 0.5f, -0.5f, 0.0, 1.0, 0.0, 0.0, 0.0,// bot-left  top face
	 -0.5f, 0.5f, -0.5f, 0.0, 1.0, 0.0, 0.0, 0.0,// bot-right top face
	 -0.5f, 0.5f, 0.5f, 0.0, 1.0, 0.0, 0.0, 0.0,// top-right  top face
	 0.5f, 0.5f, 0.5f, 0.0, 1.0, 0.0, 0.0, 0.0,// top-left top face

	 0.5f, -0.5f, -0.5f, 0.0, -1.0, 0.0, 0.0, 0.0,// bot-left  bot face
	 -0.5f, -0.5f, -0.5f, 0.0, -1.0, 0.0, 0.0, 0.0,// bot-right bot face
	 -0.5f, -0.5f, 0.5f, 0.0, -1.0, 0.0, 0.0, 0.0,// top-right  bot face
	 0.5f, -0.5f, 0.5f, 0.0, -1.0, 0.0, 0.0, 0.0,// top-left bot face
};

static float skyBoxVertex [] =
{
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 - 1.0f, 1.0f, -1.0f,

	 - 1.0f, -1.0f, -0.5,
	 - 1.0f, -1.0f, 1.0f,
	 - 1.0f, 1.0f, 1.0f,
	 -1.0f, 1.0f, -1.0f,

	 - 1.0f, -1.0f, 1.0f,
	 1.0f, -1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	 -1.0f, 1.0f, 1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, -1.0f,

	 1.0f, 1.0f, -1.0f,
	 -1.0f, 1.0f, -1.0f
	 - 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,

	 1.0f, -1.0f, -1.0f,
	 - 1.0f, -1.0f, -0.5,
	 - 1.0f, -1.0f, 1.0f,
	 1.0f, -1.0f, 1.0f,
};

static uint32_t indicesCube[] = {
	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9, 10,
	10, 11, 8,

	12, 13, 14,
	14, 15, 12,

	16, 17, 18,
	18, 19, 16,

	20, 21, 22,
	22, 23, 20
};

namespace Core
{
	std::unordered_map<std::string, std::shared_ptr<Core_Renderer::Shader>> ResourceManager::mShaders = std::unordered_map<std::string, std::shared_ptr<Core_Renderer::Shader>>();
	std::unordered_map<std::string, std::shared_ptr<Core_Renderer::Texture>> ResourceManager::mTextures = std::unordered_map<std::string, std::shared_ptr<Core_Renderer::Texture>>();
	std::unordered_map<std::string, std::shared_ptr<Core_Renderer::VertexArray>> ResourceManager::mVertexArrays = std::unordered_map<std::string, std::shared_ptr<Core_Renderer::VertexArray>>();
	std::unordered_map<std::string, std::shared_ptr<Material>> ResourceManager::mMaterials = std::unordered_map<std::string, std::shared_ptr<Material>>();

	std::once_flag flag1;
void ResourceManager::Initilize()
{
	
	std::call_once(flag1, []() {
		// Load default resources
		uint32_t color = 0xffffffff;
		LoadTexture(&color, 1, 1, "White");
		std::vector<std::string> skyBoxFiles;

		Core_Renderer::CubeMapFilePath skyboxFilePaths = 
		{
			"skyrender0001.bmp",
			"skyrender0002.bmp",
			"skyrender0003.bmp",
			"skyrender0004.bmp",
			"skyrender0005.bmp",
			"skyrender0006.bmp"
		};
		
		LoadCubeMap(skyboxFilePaths, "Skybox");
		LoadShader("BasicShader.glsl", "Default");
		LoadShader("Skybox.glsl", "Skybox");

		const auto& defaultMaterial = std::make_shared<DefaultMaterial>();
		mMaterials.insert(std::make_pair("Default", defaultMaterial));

		const auto& skyBoxMaterial = std::make_shared<SkyboxMaterial>();
		mMaterials.insert(std::make_pair("Skybox", skyBoxMaterial));

		auto IboCube = std::make_shared<Core_Renderer::IndexBuffer>(indicesCube, 36);
		auto VboCube = std::make_shared<Core_Renderer::VertexBuffer>(vertexDataCube, 24 * 8 * sizeof(float), 24);

		{
			Core_Renderer::BufferLayout layout = {
				{Core_Renderer::ShaderDataType::Float3, "a_Position"},
				{Core_Renderer::ShaderDataType::Float3, "a_Normals" },
				{Core_Renderer::ShaderDataType::Float2, "a_TexCoord" },
			};
			VboCube->SetLayout(layout);
		}

		auto IboQuad = std::make_shared<Core_Renderer::IndexBuffer>(indicesCube, 6); //Only taking the front face of the cube
		auto VboQuad = std::make_shared<Core_Renderer::VertexBuffer>(vertexDataCube, 4 * 8 * sizeof(float), 4);

		{
			Core_Renderer::BufferLayout layout = {
				{Core_Renderer::ShaderDataType::Float3, "a_Position"},
				{Core_Renderer::ShaderDataType::Float3, "a_Normals" },
				{Core_Renderer::ShaderDataType::Float2, "a_TexCoord" },
			};
			VboQuad->SetLayout(layout);
		}

		auto IboSkybox = std::make_shared<Core_Renderer::IndexBuffer>(indicesCube, 36);
		auto VboSkybox = std::make_shared<Core_Renderer::VertexBuffer>(skyBoxVertex, 24 * 3 * sizeof(float), 24);

		{
			Core_Renderer::BufferLayout layout = {
				{Core_Renderer::ShaderDataType::Float3, "a_Position"},
			};
			VboSkybox->SetLayout(layout);
		}
		
		LoadVertexArray(VboCube, IboCube, "Cube");
		
		LoadVertexArray(VboQuad, IboQuad, "Quad");

		LoadVertexArray(VboSkybox, IboSkybox, "Skybox");

		LoadVertexArray(CUBE_FILE_NAME, "Cube2");

		LoadVertexArray(SPHERE_FILE_NAME, "Sphere");

		LoadVertexArray(MONKEY_FILE_NAME, "Monkey");

	});
}
void ResourceManager::Shutdown()
{
}

std::shared_ptr<Core_Renderer::Texture> ResourceManager::LoadTexture(const void* data, const uint32_t width,  const uint32_t height, const std::string& name)
{
	auto& texture = std::make_shared<Core_Renderer::Texture>(data, width, height);
	mTextures.insert(std::make_pair(name, texture));
	return texture;
}

std::shared_ptr<Core_Renderer::Texture> ResourceManager::LoadTexture(const std::string& filename, const std::string& name)
{
	const auto& fp = PATH_TO_TEXTURES + std::string(filename);
	auto& texture = std::make_shared<Core_Renderer::Texture>(fp);
	mTextures.insert(std::make_pair(name, texture));
	return texture;
}

std::shared_ptr<Core_Renderer::Cubemap> ResourceManager::LoadCubeMap(const Core_Renderer::CubeMapFilePath& filePaths, const std::string& name)
{
	const Core_Renderer::CubeMapFilePath files {
		PATH_TO_SKYBOX + filePaths.Right,
		PATH_TO_SKYBOX + filePaths.Left,
		PATH_TO_SKYBOX + filePaths.Top,
		PATH_TO_SKYBOX + filePaths.Bottom,
		PATH_TO_SKYBOX + filePaths.Front,
		PATH_TO_SKYBOX + filePaths.Back};
	const auto cubeMap = std::make_shared<Core_Renderer::Cubemap>(files);
	mTextures.insert(std::make_pair(name, cubeMap));
	return cubeMap;
}

std::shared_ptr<Core_Renderer::Shader> ResourceManager::LoadShader(const std::string& filename, const std::string& name)
{
	const auto& fp = PATH_TO_SHADERS + std::string(filename);
	auto& shader = Core_Renderer::LoadShader(fp);
	mShaders.insert(std::make_pair(name, shader));
	return shader;
}

std::shared_ptr<Core_Renderer::VertexArray> ResourceManager::LoadVertexArray(const std::string& filename, const std::string& name)
{
	const auto& fp = PATH_TO_MODELS + std::string(filename);
	const auto& modelCube = LoadObj(fp);
	if (!modelCube.has_value())
		return nullptr;
	mVertexArrays.insert(std::make_pair(name, modelCube.value()));
	return modelCube.value();
}

std::shared_ptr<Core_Renderer::VertexArray> ResourceManager::LoadVertexArray(const std::shared_ptr<Core_Renderer::VertexBuffer>& vb,
	const std::shared_ptr<Core_Renderer::IndexBuffer>& ib, const std::string& name)
{
	auto& va = std::make_shared<Core_Renderer::VertexArray>();
	va->AddVertexBuffer(vb);
	va->SetIndexBuffer(ib);
	mVertexArrays.insert(std::make_pair(name, va));
	return va;
	
}
void ResourceManager::LoadMaterial(const std::shared_ptr<Material> mat, const std::string& name)
{
	mMaterials.insert(std::make_pair(name, mat));
}

std::optional<std::shared_ptr<Core_Renderer::Texture>> ResourceManager::GetTexture(const std::string& name)
{
	if(mTextures.find(name) == mTextures.end())
		return { };
	return mTextures.at(name);
}

std::optional<std::shared_ptr<Core_Renderer::Shader>> ResourceManager::GetShader(const std::string& name)
{
	if (mShaders.find(name) == mShaders.end())
		return { };
	return mShaders.at(name);
}

std::optional<std::shared_ptr<Core_Renderer::VertexArray>> ResourceManager::GetVertexArray(const std::string& name)
{
	if (mVertexArrays.find(name) == mVertexArrays.end())
		return { };
	return mVertexArrays.at(name);
}

std::optional<std::shared_ptr<Material>> ResourceManager::GetMaterial(const std::string& name)
{
	if (mMaterials.find(name) == mMaterials.end())
		return { };
	return mMaterials.at(name);
}

std::shared_ptr<Core_Renderer::Texture> ResourceManager::GetWhiteTexture()
{
	return mTextures.at("White");
}

const std::shared_ptr<Core_Renderer::Shader> ResourceManager::GetDefaultShader()
{
	return mShaders.at("Default");
}

const std::shared_ptr<Core_Renderer::VertexArray> ResourceManager::GetQuadVertexArray()
{
	return mVertexArrays.at("Quad");
}

const std::shared_ptr<Core_Renderer::VertexArray> ResourceManager::GetCubeVertexArray()
{
	return mVertexArrays.at("Cube");
}

const std::shared_ptr<Core_Renderer::VertexArray> ResourceManager::GetSphereVertexArray()
{
	return mVertexArrays.at("Sphere");
}

std::shared_ptr<Material> ResourceManager::GetDefaultMaterial()
{
	return mMaterials.at("Default");
}
} // namespace Core