#include "stdafx.h"
#include "../include/Mesh.h"
#include "../include/ResourceManager.h"

namespace Core
{
Mesh::Mesh()
{
	mVertexArray = ResourceManager::GetInstance().GetCubeVertexArray();
	mMaterial = ResourceManager::GetInstance().GetDefaultMaterial();
}
Mesh::Mesh(std::shared_ptr<Core_Renderer::VertexArray> vertexArray, 
	std::shared_ptr<Material> material)	
	:	mVertexArray(vertexArray), 
		mMaterial(material)
{
}
}
