#pragma once
#include <vector>
#include "AABB.h"
#include "FloodFill.h"
#include "Triangle.h"
#include "Voxel.h"

struct NavMeshInfo
{
	AABB3DF box;
	std::vector<Triangle> triangles;
};

struct NavMesh
{
	using validator = bool(*)(const Triangle&);
	static NavMeshInfo  EraseFalseTriangle(const std::vector<Triangle>& vec,validator fnValidator);
	static NavMeshInfo CreateNavMesh(const std::vector<Triangle>& vec);
    template<Dir dir>
    static bool DirValidator(const Triangle& triangle);
	static void ResizeNavMesh(NavMeshInfo& box,const Vector3F& voxelSize);
	static Grid2d<Voxel> GenerateGrid(const NavMeshInfo& info, const Vector3F& voxelSize);

};

template <Dir dir>
bool NavMesh::DirValidator(const Triangle& triangle)
{
	return triangle.GetNormal().normalize() == Vector3F::Dir<dir>();
}
