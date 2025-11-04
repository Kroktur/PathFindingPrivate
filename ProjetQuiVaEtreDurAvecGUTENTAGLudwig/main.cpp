#include <vector>
#include <iostream>
#include <deque>

struct Grid
{
    int height, width;

    int getIndex(int raw, int col) const
    {
        return raw * width + col;
    }

    std::vector<int> data;

    Grid(int value) : data(), height(value), width(value)
    {
        data.resize(height * width);
    }

    int& operator[](int index)
    {
        return data[index];
    }

    void SetGrid(int tab[100])
    {
        for (int i = 0; i < (width * height); ++i)
        {
            data[i] = tab[i];
        }
    }

    void drawGrid()
    {
        for (int i = 0; i < height; ++i)
        {
            for (auto j = 0; j < width; ++j)
            {
                std::cout << data[i * width + j] << " ";
            }
            std::cout << "\n";
        }
    }
};

struct Floodfill
{
    static void FloodFill(Grid& tab, size_t index)
    {
        std::deque<int> indexVect;
        indexVect.push_back(index);

        while (!indexVect.empty())
        {
            auto currentIndex = indexVect.front();
            indexVect.pop_front();
            auto symbol = tab[currentIndex];

            size_t raw = currentIndex / tab.width;
            size_t col = currentIndex - raw * tab.width;

            if (symbol != 1)
            {
                continue;
            }

            tab[currentIndex] = 0;

            if (raw != 0)
                indexVect.push_back(tab.getIndex(raw - 1, col));

            if (raw != tab.height - 1)
                indexVect.push_back(tab.getIndex(raw + 1, col));

            if (col != 0)
                indexVect.push_back(tab.getIndex(raw , col-1));

            if (col != tab.width - 1)
                indexVect.push_back(tab.getIndex(raw, col+1));
        }
    }
};

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