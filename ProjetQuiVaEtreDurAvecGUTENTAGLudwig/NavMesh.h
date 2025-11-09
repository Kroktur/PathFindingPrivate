#pragma once
#include <vector>

#include "AABB.h"
#include "Triangle.h"
struct NavMeshInfo
{
	AABB3DF box;
	std::vector<Triangle> triangles;
};

struct NavMesh
{
	using validator = bool(*)(const Triangle&);
	static NavMeshInfo  EraseFalseTriangle(const std::vector<Triangle>& vec,validator fnValidator);
    template<Dir dir>
    static bool DirValidator(const Triangle& triangle);
	AABB3DF ResizeBox(const NavMeshInfo& box,const Vector2F& size) const 
	{
		return box.box;
	}
};

template <Dir dir>
bool NavMesh::DirValidator(const Triangle& triangle)
{
	return triangle.GetNormal().normalize() == Vector3F::Dir<dir>();
}
