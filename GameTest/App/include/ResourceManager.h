#pragma once

#include <memory>
#include <unordered_map>
#include <optional>


namespace Core_Renderer
{
struct Shader;
class Texture;
class VertexBuffer;
class IndexBuffer;
class VertexArray;
class Cubemap;
struct CubeMapFilePath;
}

namespace Core
{
class Material;

class ResourceManager
{
public:
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	ResourceManager(const ResourceManager&) = delete;

	ResourceManager& operator=(const ResourceManager&) = delete;

	static void Initilize();

	static void Shutdown();

	static std::shared_ptr<Core_Renderer::Texture> LoadTexture(const void* data, const uint32_t width, const uint32_t height, const std::string& name);

	static std::shared_ptr<Core_Renderer::Texture> LoadTexture(const std::string& filename, const std::string& name);

	static std::shared_ptr<Core_Renderer::Cubemap> LoadCubeMap(const Core_Renderer::CubeMapFilePath& filePaths, const std::string& name);

	static std::shared_ptr<Core_Renderer::Shader> LoadShader(const std::string& filename, const std::string& name);

	static std::shared_ptr<Core_Renderer::VertexArray> LoadVertexArray(const std::string& filename, const std::string& name);

	static std::shared_ptr<Core_Renderer::VertexArray> LoadVertexArray(const std::shared_ptr<Core_Renderer::VertexBuffer>& vb, 
		const std::shared_ptr<Core_Renderer::IndexBuffer>& ib, const std::string& name);

	static void LoadMaterial(std::shared_ptr<Material> mat, const std::string& name);

	static std::optional<std::shared_ptr<Core_Renderer::Texture>> GetTexture(const std::string& name);
			 
	static  std::optional<std::shared_ptr<Core_Renderer::Shader>> GetShader(const std::string& name);
			 
	static  std::optional<std::shared_ptr<Core_Renderer::VertexArray>> GetVertexArray(const std::string& name);
			 
	static  std::optional<std::shared_ptr<Material>> GetMaterial(const std::string& name);

	static std::shared_ptr<Core_Renderer::Texture> GetWhiteTexture();
	
	static const std::shared_ptr<Core_Renderer::Shader> GetDefaultShader();
	
	static std::shared_ptr<Material> GetDefaultMaterial();

	static const std::shared_ptr<Core_Renderer::VertexArray> GetQuadVertexArray();

	static const std::shared_ptr<Core_Renderer::VertexArray> GetCubeVertexArray();

	static const std::shared_ptr<Core_Renderer::VertexArray> GetSphereVertexArray();

private:
	
	static std::unordered_map<std::string, std::shared_ptr<Core_Renderer::Texture>> mTextures;

	static std::unordered_map<std::string, std::shared_ptr<Core_Renderer::Shader>> mShaders;

	static std::unordered_map<std::string, std::shared_ptr<Core_Renderer::VertexArray>> mVertexArrays;

	static std::unordered_map<std::string, std::shared_ptr<Material>> mMaterials;
	
	ResourceManager() = default;

	~ResourceManager() = default;
};

}