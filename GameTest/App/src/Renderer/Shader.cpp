#include "stdafx.h"
#include "../../include/Renderer/Shader.h"
#include "../../include/Renderer/Constants.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Math/Mat4x4.h"
#include "Logger.h"
#include <fstream>
#include <sstream>


namespace Core_Renderer
{
Shader::Shader(const std::string& filename)
	: mRendererID(0)
{
	mFilePath = PATH_TO_SHADERS + filename;
	auto [vertexShader, fragmentShader] = ParseShader(mFilePath);
	mRendererID = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(mRendererID);
}

void Shader::Bind() const
{
	glUseProgram(mRendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
	glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, const Core_Math::Mat4x4& m4x4)
{
	auto p = &m4x4[0][0];
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &m4x4[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	int loc = glGetUniformLocation(mRendererID, name.c_str()); 
	if(loc == -1)
	{
		LOG_ERROR("Uniform {} doesn't exist", name);
	}
	return loc;
}
std::tuple<std::string, std::string> Shader::ParseShader(const std::string& fp)
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	
	std::ifstream stream(fp);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;


	while (std::getline(stream, line))
	{
		if(line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	mShaderSource = ss[0].str() + '\n' + ss[1].str();

	return {ss[0].str(), ss[1].str()};
}

ShaderID Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	ShaderID programId = glCreateProgram();
	ShaderID vertexShaderId = CompileShader(vertexShader, GL_VERTEX_SHADER);
	ShaderID fragmentShaderId = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	//Link the shaders to the program
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glValidateProgram(programId);
	
   //Delete the shaders
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);


	return programId;
}

uint32_t Shader::CompileShader(const std::string& source, uint32_t type)
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
