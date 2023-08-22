#pragma once
#include "../../include/CollisionDetection/AABB.h"

namespace Core_Physics
{

AABB Union(const AABB& a, const AABB& b)
{
	AABB result;
	result.MaxPoint = Core_Math::Vector3::Max(a.MaxPoint, b.MaxPoint);
	result.MinPoint = Core_Math::Vector3::Min(a.MinPoint, b.MinPoint);
	return result;
}

AABB Intersection(const AABB& a, const AABB& b)
{
	AABB result;
	result.MaxPoint = Core_Math::Vector3::Min(a.MaxPoint, b.MaxPoint);
	result.MinPoint = Core_Math::Vector3::Max(a.MinPoint, b.MinPoint);
	return result;
}

bool CheckOverlap(const AABB& a, const AABB& b)
{
	return	(a.MaxPoint.x >= b.MinPoint.x) && (a.MinPoint.x <= b.MaxPoint.x) &&
		(a.MaxPoint.y >= b.MinPoint.y) && (a.MinPoint.y <= b.MaxPoint.y) &&
		(a.MaxPoint.z >= b.MinPoint.z) && (a.MinPoint.z <= b.MaxPoint.z);
}

bool IsContained(const AABB& container, const AABB& containee)
{
	return	(container.MaxPoint.x >= containee.MaxPoint.x) && (container.MinPoint.x <= containee.MinPoint.x) &&
		(container.MaxPoint.y >= containee.MaxPoint.y) && (container.MinPoint.y <= containee.MinPoint.y) &&
		(container.MaxPoint.z >= containee.MaxPoint.z) && (container.MinPoint.z <= containee.MinPoint.z);
}
}