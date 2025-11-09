
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

static constexpr bool grille[] = {
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
	//Grid2d<bool,10> t{};
	//t[Dimension2d<10>::GetIndex(1, 1)] = true;
	//Grid2d<bool, 10 > t2;
	//t2 = grille;
	//
	//	t2.DrawGrid();
	//	if (_getch())
	//	{
	//		FloodFill<bool, 10>::Iterative< [](const bool& b) {return b == true; }, [](bool& b) {b = false; } > (t2, Dimension2d<10>::GetIndex(1, 1));}
	//	std::cout << "\n";
	//	t2.DrawGrid();



	Vertex A1;
	Vertex A2;
	Vertex A3;
	A1.position = Vector3F{ 4.0f, 0.0f, 2.0f };
	A2.position = Point3F{ 5.0f, 0.0f, 2.0f };
	A3.position = Point3F{ 3.0f, 0.0f, 6.0f };
	auto result = VectorND<float, 4>::Dir<Dir::FORWARD>();

	auto resultNav = NavMesh::EraseFalseTriangle(std::vector<Triangle>{Triangle{ A1,A3,A2 }}, NavMesh::DirValidator<Dir::UP>);

	std::cout << resultNav.triangles.size();
}
