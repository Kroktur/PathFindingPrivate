#include <iostream>
#include <vector>
#include <array>
#include <conio.h>

#include "PathFinding.h"


int main()
{
	Grid2d<bool,10> t{};
	t[Dimention2d<10>::GetIndex(1, 1)] = true;
	Grid2d<bool, 10 > t2;
	t2 = grille;
	
		t2.DrawGrid();
		if (_getch())
		{
			FloodFillIterative(t2, Dimention2d<10>::GetIndex(1, 1),true);
		}
		std::cout << "\n";
		t2.DrawGrid();


	//FloodFill(t2,Grid2d<10>::GetIndex(1,1));
	//FloodFillFn(t2, Dimention2d<10>::GetIndex(7, 8));
	//FloodFillIterative(t2, Dimention2d<10>::GetIndex(1, 1));
	//FloodFillIterative(t2, Grid2d<10>::GetIndex(7, 8));
	
}
