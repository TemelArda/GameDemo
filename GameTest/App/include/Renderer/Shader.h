#pragma once
#include <string>
#include <tuple>

namespace Core_Math
{
	class Mat4x4;
}

namespace Core_Renderer
{
using ShaderID = unsigned int;
class Shader
{

public:
	Shader(const std::string& fileName);

	~Shader();

	void Bind() const;

	void Unbind() const;

	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);

	void SetUniform1f(const std::string& name, float value);

	void SetUniform1i(const std::string& name, int value);

	void SetUniformMat4f(const std::string& name, const Core_Math::Mat4x4& m4x4);

private:

	ShaderID mRendererID;

	std::string mFilePath;

	std::string mShaderSource;

	int GetUniformLocation(const std::string& name);
	
	std::tuple<std::string, std::string> ParseShader(const std::string& fp);

	ShaderID CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	
	ShaderID CompileShader(const std::string& source, uint32_t type);

};

}