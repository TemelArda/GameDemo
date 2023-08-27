#include "stdafx.h"
#include "../../include/Renderer/Shader.h"
#include <GL/glew.h>
#include "Math/Mat4x4.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <tuple>


namespace Core_Renderer
{

using ShaderID = uint32_t;

int GetUniformLocation(const ProgramID& id, const std::string& name);

std::tuple<const std::string, const std::string, const std::string>  ParseShader(const std::string& fp);

ProgramID CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geomShader = "");

ShaderID CompileShader(const std::string& source, uint32_t type);

std::shared_ptr<Shader> LoadShader(const std::string& filePath)
{
	std::shared_ptr<Shader> s = std::make_unique<Shader>();

	s->FilePath = filePath;
	auto& [vertexShader, fragmentShader, geomShader] = ParseShader(filePath);
	s->Id = CreateShader(vertexShader, fragmentShader, geomShader);
	
	return s;
}

Shader::~Shader()
{
	glDeleteProgram(Id);
}

void SetUniform4f(const ProgramID& id, const std::string& name, float v1, float v2, float v3, float v4)
{
	glUniform4f(GetUniformLocation(id, name), v1, v2, v3, v4);
}

void SetUniform4f(const ProgramID& id, const std::string& name, Core_Math::Vector4 values)
{
	glUniform4f(GetUniformLocation(id, name), values.x, values.y, values.z, values.w);
}

void SetUniform3f(const ProgramID& id, const std::string& name, float v1, float v2, float v3)
{
    glUniform3f(GetUniformLocation(id, name), v1, v2, v3);
}

void SetUniform3f(const ProgramID& id, const std::string& name, Core_Math::Vector3 values)
{
	glUniform3f(GetUniformLocation(id, name), values.x, values.y, values.z);
}

void SetUniform1f(const ProgramID& id, const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(id, name), value);
}

void SetUniform1i(const ProgramID& id, const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(id, name), value);
}

void SetUniformMat4f(const ProgramID& id, const std::string& name, const Core_Math::Mat4x4& m4x4)
{
	glUniformMatrix4fv(GetUniformLocation(id, name), 1, GL_TRUE, &m4x4[0][0]);
}

void SetUniformMat4f(const ProgramID& id, const std::string& name, const Core_Math::Mat4x4&& m4x4)
{
	glUniformMatrix4fv(GetUniformLocation(id, name), 1, GL_TRUE, &m4x4[0][0]);
}

int GetUniformLocation(const ProgramID& id, const std::string& name)
{
	int loc = glGetUniformLocation(id, name.c_str());
	if (loc == -1)
	{
		LOG_ERROR("Uniform {} doesn't exist", name);
	}
	return loc;
}
std::tuple<const std::string, const std::string, const std::string> ParseShader(const std::string& fp)
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
	};
	
	std::ifstream stream(fp);
	std::string line;
	std::stringstream ss[3];
	ShaderType type = ShaderType::NONE;


	while (std::getline(stream, line))
	{
		if(line.find("#type") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
			else
				type = ShaderType::GEOMETRY;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	//mShaderSource = ss[0].str() + '\n' + ss[1].str();
	stream.close();
	return {ss[0].str(), ss[1].str(), ss[2].str()};
}

ProgramID CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geomShader)
{
	ProgramID id = glCreateProgram();
	
	ShaderID vertexShaderId = CompileShader(vertexShader, GL_VERTEX_SHADER);
	glAttachShader(id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	
	ShaderID fragmentShaderId = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
	glAttachShader(id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

	if (!geomShader.empty())
	{
		ShaderID geometryShaderId = CompileShader(geomShader, GL_GEOMETRY_SHADER);
		glAttachShader(id, geometryShaderId);
		//glDeleteShader(geometryShaderId);
	}

	//Link the shaders to the program
	GLint params = 0;
	glLinkProgram(id);
	glValidateProgram(id);
	glGetProgramiv(id,
		GL_VALIDATE_STATUS,
		&params);
	if (params != GL_TRUE)
	{
		LOG_ERROR("Shader program {} failed to validate", id);
	}
	return id;
}

ShaderID CompileShader(const std::string& source, uint32_t type)
{
	ShaderID id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	
	//Error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		LOG_ERROR("Failed to compile {} shader", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
		LOG_ERROR("{}", message);
		glDeleteShader(id);
		return 0;
	}
	return id;
}

}
