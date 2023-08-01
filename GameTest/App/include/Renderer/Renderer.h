#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace Core_Renderer
{
class Renderer
{
public:
	static Renderer& GetInstance()
	{
		static Renderer instance;
		return instance;
	}

	static void Render(const VertexArray* vao, const IndexBuffer* Ibo, const Shader* shader);

	static void PrintOpenGLVersion();
private:
	Renderer() = default;
	~Renderer() = default;

};
}