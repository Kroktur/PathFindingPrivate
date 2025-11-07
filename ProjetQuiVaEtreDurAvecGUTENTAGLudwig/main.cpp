#include "FloodFill.h"

int main()
{
    static int grille[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    Point A = { 2,5,0 };
    Point B = { 5,2,0 };
    Point C = { 8,6,0 };

    Grid grid(10);
    Triangle triangle(A, B, C);
    
    grid.SetGrid(grille);
    grid.drawGrid();
    std::cout << "\n";
    Floodfill::FloodFill(grid, triangle);
    grid.drawGrid();
    return 0;
}