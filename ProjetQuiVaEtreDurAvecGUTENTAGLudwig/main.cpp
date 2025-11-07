#include <iostream>
#include <vector>
#include <array>
#include <conio.h>
#include "FloodFill.h"
#include "Matrix.h"
#include "Triangle.h"
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
	A1.position = Vector3F{ 0.0f, 0.0f, 0.0f };
	A2.position = Point3F{ 4.0f, 0.0f, 0.0f};
	A3.position = Point3F{ 2.0f, 3.0f, 0.0f };

	//Vector3F A(0.0f, 0.0f, 0.0f);
	//Vector3F B(4.0f, 0.0f, 0.0f);
	//Vector3F C(2.0f, 3.0f, 0.0f);

	Triangle2d triangle;
	triangle.points = {A1,A2,A3};
	auto result = triangle.GetCircumcenter();
	std::cout << result;
	//FloodFill(t2,Grid2d<10>::GetIndex(1,1));
	//FloodFillFn(t2, Dimension2d<10>::GetIndex(7, 8));
	//FloodFillIterative(t2, Dimension2d<10>::GetIndex(1, 1));
	//FloodFillIterative(t2, Grid2d<10>::GetIndex(7, 8));
	
}
