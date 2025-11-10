
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
	Grid2d<int> t{Dimension2d(10,10)};
	t[Dimension2dStatic<10>::GetIndex(1, 1)] = 1;
	Grid2d<int> t2{ Dimension2d(10,10) ,grille,100 };

	
		t2.DrawGrid();
		if (_getch())
		{
			FloodFill<int>::Iterative< [](const int& b) {return b == 1; }, [](int& b) {b = 0; } > (t2, Dimension2dStatic<10>::GetIndex(1, 1));}
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

	std::cout << resultNav.triangles.size();
}
