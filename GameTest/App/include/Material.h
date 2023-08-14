#pragma once
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include <memory>
#include "Math/Vector4.h"


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

class  DefaultMaterial : public Material
{
public:
	Core_Math::Vector4 AmbientColor;

	Core_Math::Vector4 DiffuseColor;

	Core_Math::Vector4 SpecularColor;

	float SpecularPower;

	std::shared_ptr<Core_Renderer::Texture> Texture;

public:
	DefaultMaterial();

	DefaultMaterial(const std::shared_ptr<Core_Renderer::Shader>& mShader);

	DefaultMaterial(const std::shared_ptr<Core_Renderer::Shader>& mShader, const std::shared_ptr<Core_Renderer::Texture>& t);

	~DefaultMaterial() = default;

	virtual std::shared_ptr<Core_Renderer::Shader> GetShader() const override
	{
		return mShader;
	}

	virtual void Bind() override
	{
		mShader->Bind();
		Texture->Bind();
		mShader->SetUniform1i("u_Texture", 0);
		mShader->SetUniform4f("u_AmbientProduct", AmbientColor);
		mShader->SetUniform4f("u_DiffuseColor", DiffuseColor);
		mShader->SetUniform4f("u_SpecularColor", SpecularColor);
		mShader->SetUniform1f("u_SpecularPower", SpecularPower);
	}

	virtual void Unbind() override
	{
		mShader->Unbind();
		Texture->Unbind();
	}

	virtual MaterialID GetMaterialID() override
	{
		return mId;
	}

	virtual uint32_t GetShaderID() override;
private:

	std::shared_ptr<Core_Renderer::Shader> mShader;

	MaterialID mId;

};
}