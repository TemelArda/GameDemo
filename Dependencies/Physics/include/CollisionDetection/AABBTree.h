#pragma once
#include "AABB.h"
#include <vector>
#include <unordered_map>


namespace Core_Physics
{

using EntityID = uint32_t;
using NodeIndex = uint32_t;
using EntityToNodeIndex = std::unordered_map<EntityID, NodeIndex>;

struct AABBNode
{
	EntityID entityID;
	
	NodeIndex parent;
	
	NodeIndex left;
	
	NodeIndex right;
	
	AABB aabb;

	bool isLeaf;
};

class AABBTree
{
public:
	
	void InserObject(EntityID entityId, const AABB& aabb);

	void RemoveObject(EntityID entityId);

	void UpdateObject(EntityID entityId, const AABB& aabb);


private:

	std::vector<AABBNode> mNodes;

	EntityToNodeIndex mEntityToIndexMap;
	
	NodeIndex mRoot;
	
	uint32_t mNodeCount;
	
	uint32_t mNodeCapacity;
	
	uint32_t mFreeList;
};
}