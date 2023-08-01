#pragma once


namespace Core{
struct Color
{
	Color()
		: r(1.0), g(1.0), b(1.0) 
	{
	};
	Color(float color )
		: r(color), g(color), b(color) 
	{
	}

	Color(float red, float green, float blue)
		: r(red), g(green), b(blue) 
	{
	};

	Color(const Color& color)
		: r(color.r), g(color.g), b(color.b) 
	{
	};

	Color& operator=(const Color& other)
	{
		if (this == &other)
			return *this;
		r = other.r;
		g = other.g;
		b = other.b;
		return *this;
	}

	float r;
	
	float g;
	
	float b;
	
};
}
