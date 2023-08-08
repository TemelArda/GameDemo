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
}
