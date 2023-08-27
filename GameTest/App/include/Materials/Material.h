#pragma once
#include <memory>

namespace Core_Renderer
{
class Shader;
}


namespace Core
{
using MaterialID = uint32_t;

class Material
{
public:
	//implement rule of 5
	
	Material() = default;

	~Material() = default;

	Material(const Material& other) = default;

	Material(Material&& other) = default;

	Material& operator=(const Material& other) = default;

	Material& operator=(Material&& other) = default;

	virtual void Bind() = 0;

	virtual void Unbind() = 0;

	virtual MaterialID GetMaterialID() = 0;

	virtual uint32_t GetShaderID() = 0;

	virtual std::shared_ptr<Core_Renderer::Shader> GetShader() const = 0;
protected :
	static MaterialID mNextMaterialId;
};
}