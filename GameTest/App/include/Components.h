#pragma once
#include <string>
#include "./Color.h"
#include "./Math/Vector2.h"

namespace Core
{

struct MovementComponent
{
	Core_Math::numeral baseSpeed = 30.0f;
	
	Core_Math::Vector2 velocity; // Change to vector 

	Core_Math::Vector2 acceleration; // Change to vector

};

struct Transform2DComponent
{
	Transform2DComponent()
		: scale(1.0f), rotation(0.0f)
	{
		
	}

	Transform2DComponent(float x, float y, float scale, float rotation)
		: scale(scale), rotation(rotation)
	{
		position.x = x;
		position.y = y;
	}
		
	Core_Math::Vector2 position;
	
	Core_Math::numeral  scale;

	Core_Math::numeral  rotation;
};

struct ShapeRendererComponent
{
	Core::Color color;

	bool isFilled = false;

	float lineWidth = 1.0f;
};


struct CircleRendererComponent : public ShapeRendererComponent
{
	
	float radius = 1.0f;

	float offSetx = 0.0f;

	Core_Math::Vector2 offSet;
};

struct RectangleRendererComponent : public ShapeRendererComponent
{
	float width = 5;

	float height = 2.5;

	Core_Math::Vector2 offSet;
};

struct LineRendererComponent : public ShapeRendererComponent
{
	Core_Math::Vector2 p1;

	Core_Math::Vector2 p2;
};

struct TriangleRendererComponent : public ShapeRendererComponent
{
	Core_Math::Vector2 offSet;

	float height;
};

struct SpriteRendererComponent
{
	std::string textureName;
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
