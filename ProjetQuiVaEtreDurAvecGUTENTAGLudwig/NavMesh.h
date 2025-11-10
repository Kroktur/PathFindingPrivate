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
    template<Dir dir>
    static bool DirValidator(const Triangle& triangle);
	static void ResizeNavMesh(NavMeshInfo& box,const Vector3F& voxelSize);
	static void GenerateGrid(NavMeshInfo info, const Vector3F& voxelSize)
	{
		size_t sizeX = static_cast<size_t>(info.box.Size().x / voxelSize.x);
		size_t sizeZ = static_cast<size_t>(info.box.Size().z / voxelSize.z);
		Grid2d<Voxel> grid(Dimension2d(sizeX,sizeZ));
	}
};

template <Dir dir>
bool NavMesh::DirValidator(const Triangle& triangle)
{
	return triangle.GetNormal().normalize() == Vector3F::Dir<dir>();
}
