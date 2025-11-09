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
