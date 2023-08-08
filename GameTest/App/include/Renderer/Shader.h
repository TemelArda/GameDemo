#pragma once
#include <string>
#include <tuple>

namespace Core_Math
{
	class Mat4x4;
	class Vector4;
	class Vector3;
}

namespace Core_Renderer
{
using ShaderID = unsigned int;
class Shader
{

public:
	Shader();

	Shader(const std::string& fileName);

	~Shader();

	void Bind() const;

	void Unbind() const;

	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);

	void SetUniform4f(const std::string& name, Core_Math::Vector4 values);

	void SetUniform3f(const std::string& name, float v1, float v2, float v3);
						
	void SetUniform3f(const std::string& name, Core_Math::Vector3 values);

	void SetUniform1f(const std::string& name, float value);

	void SetUniform1i(const std::string& name, int value);

	void SetUniformMat4f(const std::string& name, const Core_Math::Mat4x4& m4x4);

	const ShaderID GetID() const { return mRendererID; }

private:

	ShaderID mRendererID;

	std::string mFilePath;

	//std::string mShaderSource;

	int GetUniformLocation(const std::string& name);
	
	std::tuple<std::string, std::string> ParseShader(const std::string& fp);

	void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	
	ShaderID CompileShader(const std::string& source, uint32_t type);

};

}