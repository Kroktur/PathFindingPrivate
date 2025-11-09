#pragma once
#include "AABB.h"
#include "optional"
struct Voxel
{
	Voxel(AABB3DF box_) : box(box_), walkable(){}
	AABB3DF box;
	Vector3F Center() const
	{
		return box.Center();
	}
	std::optional<bool> walkable;
};

