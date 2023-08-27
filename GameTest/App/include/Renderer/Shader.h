#pragma once
#include <string>
#include <memory>

namespace Core_Math
{
	class Mat4x4;
	class Vector4;
	class Vector3;
}

namespace Core_Renderer
{
using ProgramID = uint32_t;

struct Shader
{
	~Shader();

	ProgramID Id{0};
	
	std::string FilePath;
};

std::shared_ptr<Shader> LoadShader(const std::string& filePath);

void SetUniform4f(const ProgramID& id, const std::string& name, float v1, float v2, float v3, float v4);

void SetUniform4f(const ProgramID& id, const std::string& name, Core_Math::Vector4 values);
						
void SetUniform3f(const ProgramID& id, const std::string& name, float v1, float v2, float v3);
						
void SetUniform3f(const ProgramID& id, const std::string& name, Core_Math::Vector3 values);
						
void SetUniform1f(const ProgramID& id, const std::string& name, float value);
										  
void SetUniform1i(const ProgramID& id, const std::string& name, int value);

void SetUniformMat4f(const ProgramID& id,const std::string& name, const Core_Math::Mat4x4& m4x4);

void SetUniformMat4f(const ProgramID& id,const std::string& name, const Core_Math::Mat4x4&& m4x4);

}