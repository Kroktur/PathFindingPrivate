#include "NavMesh.h"



NavMeshInfo NavMesh::EraseFalseTriangle(const std::vector<Triangle>& vec,validator fnValidator)
{
	if (vec.empty())
		return NavMeshInfo{};
	std::vector<Triangle> result;
	const Vector3F Amin = vec.front().points[0].position;
	const Vector3F Amax = vec.front().points[0].position;
	AABB3DF box{ Amin,Amax };
	for (auto& it : vec)
	{
		if (!fnValidator(it))
			continue;
		result.push_back(it);

		box.Expand(it.points[0].position);
		box.Expand(it.points[1].position);
		box.Expand(it.points[2].position);
	}
	if (result.empty())
		return NavMeshInfo{};
	return NavMeshInfo{ box,result };
}

NavMeshInfo NavMesh::CreateNavMesh(const std::vector<Triangle>& vec)
{
	if (vec.empty())
		return NavMeshInfo{};
	std::vector<Triangle> result;
	const Vector3F Amin = vec.front().points[0].position;
	const Vector3F Amax = vec.front().points[0].position;
	AABB3DF box{ Amin,Amax };
	for (auto& it : vec)
	{
		result.push_back(it);

		box.Expand(it.points[0].position);
		box.Expand(it.points[1].position);
		box.Expand(it.points[2].position);
	}
	if (result.empty())
		return NavMeshInfo{};
	return NavMeshInfo{ box,result };
}

void NavMesh::ResizeNavMesh(NavMeshInfo& box, const Vector3F& voxelSize)
{
	Vector3F newMin;
	Vector3F newMax;
        
	auto size = box.box.Size();
	auto center = box.box.Center();
	Vector3F newSize;
	newSize.x = std::ceil(size.x / voxelSize.x) * voxelSize.x;
	newSize.y = std::ceil(size.y / voxelSize.y) * voxelSize.y;
	newSize.z = std::ceil(size.z / voxelSize.z) * voxelSize.z;



	newMin.x = center.x - newSize.x / 2;
	newMin.y = center.y - newSize.y / 2;
	newMin.z = center.z - newSize.z / 2;


	newMax.x = center.x + newSize.x / 2;
	newMax.y = center.y + newSize.y / 2;
	newMax.z = center.z + newSize.z / 2;

	box.box = AABB3DF(newMin, newMax);
}

Grid2d<Voxel> NavMesh::GenerateGrid(const NavMeshInfo& info, const Vector3F& voxelSize)
{
	size_t sizeX = static_cast<size_t>(info.box.Size().x / voxelSize.x);
	size_t sizeZ = static_cast<size_t>(info.box.Size().z / voxelSize.z);
	Grid2d<Voxel> grid(Dimension2d(sizeX,sizeZ));
	auto startZ = info.box.Amin.z;
	for (size_t i = 0 ; i < grid.GetDim().height ; ++i)
	{
		auto startX = info.box.Amin.x;
		for (size_t j = 0 ; j < grid.GetDim().width ; ++j)
		{
			Vector3F Amin = Vector3F{ startX,info.box.Amin.y,startZ - voxelSize.z };
			Vector3F Amax = Vector3F{startX + voxelSize.x , info.box.Amax.y, startZ};
			grid.At(grid.GetDim().GetIndex(i, j)).box = AABB3DF{Amin,Amax};
			startX += voxelSize.x;
		}
		startZ -= voxelSize.z;
	}
	return grid;
}
