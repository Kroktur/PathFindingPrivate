#include <iostream>
#include <vector>
#include <array>
#include <conio.h>

#include "FloodFill.h"

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
	Grid2d<bool,10> t{};
	t[Dimension2d<10>::GetIndex(1, 1)] = true;
	Grid2d<bool, 10 > t2;
	t2 = grille;
	
		t2.DrawGrid();
		if (_getch())
		{
			FloodFill<bool, 10>::Iterative< [](const bool& b) {return b == true; }, [](bool& b) {b = false; } > (t2, Dimension2d<10>::GetIndex(1, 1));}
		std::cout << "\n";
		t2.DrawGrid();


	//FloodFill(t2,Grid2d<10>::GetIndex(1,1));
	//FloodFillFn(t2, Dimension2d<10>::GetIndex(7, 8));
	//FloodFillIterative(t2, Dimension2d<10>::GetIndex(1, 1));
	//FloodFillIterative(t2, Grid2d<10>::GetIndex(7, 8));
	
}
