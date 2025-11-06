#include "FloodFill.h"

int main()
{
    static int grille[] = {
        0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 0, 0, 0, 1, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
        0, 1, 1, 1, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 0
    };

    Grid grid(10);
    grid.SetGrid(grille);
    grid.drawGrid();
    std::cout << "\n";
    Floodfill::FloodFill(grid, 1);
    grid.drawGrid();
    return 0;
}