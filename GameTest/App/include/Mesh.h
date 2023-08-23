#pragma once
#include "Renderer/VertexArray.h"
#include "Materials/Material.h"

namespace Core
{
class Mesh
{
public:
	Mesh();

	Mesh(std::shared_ptr<Core_Renderer::VertexArray> vertexArray, std::shared_ptr<Material> material);
	
	~Mesh() = default;

	Mesh(const Mesh&) = default;

	Mesh& operator=(const Mesh&) = default;

	Mesh(Mesh&&) = default;

	Mesh& operator=(Mesh&&) = default;

	void inline SetVertexArray(const std::shared_ptr<Core_Renderer::VertexArray>& vertexArray){mVertexArray = vertexArray;}

	inline const std::shared_ptr<Core_Renderer::VertexArray> GetVertexArray() const{return mVertexArray;}

	void inline SetMaterial(const std::shared_ptr<Material>& m){ mMaterial = m;}

	inline const std::shared_ptr<Material> GetMaterial() const{return mMaterial;}
private:
	std::shared_ptr<Core_Renderer::VertexArray> mVertexArray;
	
	std::shared_ptr<Material> mMaterial;
};
}