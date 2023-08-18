#include "stdafx.h"
#include "../include/ModelLoader.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include <fstream>
#include <sstream>
#include <regex>
#include "Logger.h"

namespace Core
{
std::optional<std::shared_ptr<Core_Renderer::VertexArray>> LoadObj(const std::string& path)
{
	if (path.substr(path.length() - 3) != "obj")
	{
		printf("File is not an obj file\n");
		return {};
	}

	std::ifstream stream(path, std::ifstream::in);
	std::string line;

	std::vector<Core_Math::Vector3> positions;
	std::vector<Core_Math::Vector2> texCoords;
	std::vector<Core_Math::Vector3> normals;
	
	std::vector<uint32_t> indices;
	std::vector<float> vertices;
	uint32_t index = 0;

	while (std::getline(stream, line))
	{
		std::stringstream ss(line);
		std::string word ;
		ss >> word;

		if (word == "v")
		{
			Core_Math::Vector3 position;
			ss >> position.x >> position.y >> position.z;
			positions.push_back(position);
		}
		else if (word == "vt")
		{
			Core_Math::Vector2 texCoord;
			ss >> texCoord.x >> texCoord.y;
			texCoords.push_back(texCoord);
		}
		else if (word == "vn")
		{
			Core_Math::Vector3 normal;
			ss >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (word == "f")
		{
		
			while(ss >> word)
			{
				std::regex re("/");
				std::sregex_token_iterator first{word.begin(), word.end(), re, -1}, last;
				std::vector<std::string> tokens{first, last};
				
				{
					int pos_index = std::stoi(tokens[0]) - 1;
					int norm_index = std::stoi(tokens[2]) - 1;
					

					vertices.push_back(positions[pos_index].x);
					vertices.push_back(positions[pos_index].y);
					vertices.push_back(positions[pos_index].z);
					vertices.push_back(normals[norm_index].x);
					vertices.push_back(normals[norm_index].y);
					vertices.push_back(normals[norm_index].z);
					if (std::isdigit(tokens[1][0]) != 0)
					{
						int tex_index = std::stoi(tokens[1]) - 1;
						vertices.push_back(texCoords[tex_index].x);
						vertices.push_back(texCoords[tex_index].y);
					}
					else
					{
						vertices.push_back(0);
						vertices.push_back(0);
					}

					indices.push_back(index++);
				}
			}
		}
	}
	stream.close();


	const auto va = std::make_shared<Core_Renderer::VertexArray>();
	auto Ibo = std::make_shared<Core_Renderer::IndexBuffer>(&indices[0], indices.size());
	auto Vbo = std::make_shared<Core_Renderer::VertexBuffer>(&vertices[0], index * 8 * sizeof(float), positions.size());
	Core_Renderer::BufferLayout layout = {
				{Core_Renderer::ShaderDataType::Float3, "a_Position"},
				{Core_Renderer::ShaderDataType::Float3, "a_Normals" },
				{Core_Renderer::ShaderDataType::Float2, "a_TexCoord" },
	};

	Vbo->SetLayout(layout);
	va->AddVertexBuffer(Vbo);
	va->SetIndexBuffer(Ibo);

	return va;
}
}
