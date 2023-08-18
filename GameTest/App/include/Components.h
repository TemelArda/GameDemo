#pragma once
#include <string>
#include "./Color.h"
#include "./Math/Vector2.h"
#include "./Math/Vector3.h"
#include "./Math/Transform3D.h"
#include "./Mesh.h"
#include "./Renderer/Texture.h"

namespace Core
{

struct TransformComponent
{
	Core_Math::Transform3D transform;
};

struct ColliderComponent
{
	bool isTrigger = false;

	bool isStatic = false;
};


struct RigidBodyComponent
{
	float mass = 1.0f;
	
	float drag = 0.0f;
	
	float angularDrag = 0.0f;
	
	bool useGravity = true;
	
	Core_Math::Vector3 velocity{0, 0, 0};
	
	Core_Math::Vector3 angularVelocity{0, 0, 0};
	
	Core_Math::Vector3 centerOfMass{0, 0, 0};
};

struct MeshComponent
{
	MeshComponent(std::shared_ptr<Core_Renderer::VertexArray> vertexArray, 
		std::shared_ptr<Material> material)
	{
		mesh = std::make_shared<Mesh>(vertexArray, material);
	}
	
	MeshComponent(std::shared_ptr<Mesh> mesh)
		: mesh(mesh)
	{
	}

	MeshComponent()
	{
		mesh = std::make_shared<Mesh>();
	}

	std::shared_ptr<Mesh> mesh;
};

struct SpriteRendererComponent
{
	Core_Renderer::Texture textrue;
};

struct Tag 
{
	Tag(const std::string& tag)
		: tag(tag)
	{
	}
	std::string tag;
};
}
