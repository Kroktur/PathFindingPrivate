#pragma once
#include <vector>
#include <iostream>
#include <deque>
#include <cmath>

#include "Vector3.h"
#include "Vector2.h"
#include "Triangle.h"

struct Grid
{
    int heigth, width;

    int getIndex(int raw, int col) const
    {
        return raw * heigth + col;
    }

    std::vector<int> data;

    Grid(int value) : data(), heigth(value), width(value)
    {
        data.resize(heigth * width);
    }

    int& operator[](int index)
    {
        return data[index];
    }

    void SetGrid(int tab[100])
    {
        for (int i = 0; i < (width * heigth); ++i)
        {
            data[i] = tab[i];
        }
    }

    void drawGrid()
    {
        for (int i = 0; i < heigth; ++i)
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
    static void FloodFill(Grid& tab, const Triangle& t)
    {
        Limits l = Limits::limit(t);

        for (float y = l.y_min; y <= l.y_max; y++)
        {
            for (float x = l.x_min; x <= l.x_max; x++)
            {
                Point3F P = { static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f, 0};
                if (t.testPointTriangle(P))
                {
                    int index = tab.getIndex(y, x);
                    tab[index] = 1;
                }
            }
        }

        std::deque<int> indexVect;

        for (int i = 0; i < tab.width * tab.heigth; ++i)
        {
            if (tab[i] == 1)
            {
                indexVect.push_back(i);
                break;
            }
        }

        while (!indexVect.empty())
        {
            auto currentIndex = indexVect.front();
            indexVect.pop_front();

            size_t raw = currentIndex / tab.width;
            size_t col = currentIndex - raw * tab.width;

            if (tab[currentIndex] != 1)
            {
                continue;
            }

            tab[currentIndex] = 2;

            if (raw != 0)
                indexVect.push_back(tab.getIndex(raw - 1, col));

            if (raw != tab.heigth - 1)
                indexVect.push_back(tab.getIndex(raw + 1, col));

            if (col != 0)
                indexVect.push_back(tab.getIndex(raw, col - 1));

            if (col != tab.width - 1)
                indexVect.push_back(tab.getIndex(raw, col + 1));
        }
    }
};
