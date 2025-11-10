
#include <iostream>
#include <vector>
#include <array>
#include <conio.h>
#include "FloodFill.h"
#include "Matrix.h"
#include "NavMesh.h"
#include "Triangle.h"
#include "Vector2.h"
#include "Vertex.h"

static constexpr int grille[] = {
		0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 0, 1, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 1, 1, 1, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 0
};

int main()
{
	/*Grid2d<int> t{Dimension2d(10,10)};
	t[Dimension2dStatic<10>::GetIndex(1, 1)] = 1;
	Grid2d<int> t2{ Dimension2d(10,10) ,grille,100 };

	
		t2.DrawGrid();
		if (_getch())
		{
			FloodFill<int>::Iterative< [](const int& b) {return b == 1; }, [](int& b) {b = 0; } > (t2, t2.GetDim().GetIndex(1,1));}
		std::cout << "\n";
		t2.DrawGrid();



	Vertex A1;
	Vertex A2;
	Vertex A3;
	A1.position = Vector3F{ 4.0f, 0.0f, 2.0f };
	A2.position = Point3F{ 5.0f, 0.0f, 2.0f };
	A3.position = Point3F{ 3.0f, 0.0f, 6.0f };
	auto result = VectorND<float, 4>::Dir<Dir::FORWARD>();

	auto resultNav = NavMesh::EraseFalseTriangle(std::vector<Triangle>{Triangle{ A1,A3,A2 }}, NavMesh::DirValidator<Dir::UP>);

	std::cout << resultNav.triangles.size();*/

	NavMeshInfo info;
	info.box = AABB3DF{ {0,-1.0f,0},{100,1.0f,100} };
	Vector3F voxel = {0.2f,2.0f,0.2f};
	NavMesh::ResizeNavMesh(info, voxel);
	std::cout << info.box.Amin << "\n";
	std::cout << info.box.Amax << "\n";
	auto grid = NavMesh::GenerateGrid(info, voxel);
	std::cout << grid.GetDim().Size() << "\n";
	//std::cout << grid[1].box.Amin << " " << grid[1].box.Amax;


	// testRasterisation
	for (auto it : info.triangles)
	{
		auto center = it.GetCenter();
		auto i = static_cast<int>(floor((center.x - info.box.Amin.x) / voxel.x));
		auto j = static_cast<int>(floor((center.z - info.box.Amin.z) / voxel.z));
		auto index = grid.GetDim().GetIndex(i, j);
		auto modifyFN = [it](const Voxel& voxel) ->bool
			{
				if (!it.testPointTriangle(voxel.Center()))
					return false;
				if (!voxel.lastTriangle.has_value())
					return true;
				if (voxel.lastTriangle.value() == it)
					return false;
				return true;
			};
		auto AffectationFN = [it](Voxel& voxel) -> void
			{
				voxel.lastTriangle = it;
				if (!voxel.walkable.has_value())
					voxel.walkable = true;
				if (it.GetNormal().normalize() != Vector3F::Dir<Dir::UP>())
					voxel.walkable = false;
				for (auto point : it.points)
				{
					if (!Math::IsSameValue(point.position.y,0.0f,Math::EPSILON_FLOAT))
						voxel.walkable = false;
				}
			};
		FloodFill<Voxel>::Iterative(grid, index, modifyFN, AffectationFN);
	}
}
