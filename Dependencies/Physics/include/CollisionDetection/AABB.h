#pragma once
#include "../Math/Vector3.h"


namespace Core_Physics
{
struct AABB
{
	Core_Math::Vector3 MaxPoint;
	Core_Math::Vector3 MinPoint;

	
	inline Core_Math::numeral GetSurfaceArea()
	{
		Core_Math::Vector3 diff = MaxPoint - MinPoint;
		return 2.0f * (diff.x * diff.y + diff.y * diff.z + diff.z * diff.x);
	}
	
	inline Core_Math::Vector3 GetCenter()
	{
		return (MaxPoint + MinPoint) * 0.5f;
	}

	inline Core_Math::numeral GetWidth()
	{
		return (MaxPoint.x - MinPoint.x);
	}

	inline Core_Math::numeral GetHeigth()
	{
		return (MaxPoint.y - MinPoint.y);
	}

	inline Core_Math::numeral GetDepth()
	{
		return (MaxPoint.z - MinPoint.z);
	}


	friend AABB Union(const AABB& a, const AABB& b);

	friend AABB Intersection(const AABB& a, const AABB& b);
	
	friend bool CheckOverlap(const AABB& a, const AABB& b);
	
	friend bool IsContained(const AABB& container, const AABB& containee);
};



}