#pragma once
#include <memory>

namespace Core_Renderer
{
struct Shader;
using ProgramID = uint32_t;
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

	virtual void SetUniforms() const = 0;

	virtual const MaterialID GetMaterialID() const = 0;

	virtual const Core_Renderer::ProgramID GetShaderID() const = 0;

protected :
	static MaterialID mNextMaterialId;
};
}