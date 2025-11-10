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
