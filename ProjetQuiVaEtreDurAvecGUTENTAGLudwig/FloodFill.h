#pragma once
#include <vector>
#include <iostream>
#include <deque>
#include <cmath>

struct Point
{
    float x;
    float y;
    float z;
};

struct Vec3
{
    float x;
    float y;
    float z;

    Point A;
    Point B;

    Vec3 getVector(const Point& A, const Point& B) const
    {
        return { B.x - A.x, B.y - A.y, B.z - A.z };
    }
};

Vec3 crossProduct(const Point& A, const Point& B)
{
    Vec3 AB;
    AB.getVector(A, B);

    return { A.y * B.z - A.z * B.y,
             A.z * B.x - A.x * B.z,
             A.x * B.y - A.y * B.x, };
}

float dotProduct(const Vec3& A, const Vec3& B)
{
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

struct Triangle
{
    Point A;
    Point B;
    Point C;

    Triangle(Point value) : A(value), B(value), C(value)
    { }

    bool testPointTriangle(const Point& P, const Point& A, const Point& B, const Point& C) const
    {
        Vec3 c1 = crossProduct(P, A);
        Vec3 c2 = crossProduct(P, B);
        Vec3 c3 = crossProduct(P, C);

        Vec3 normal = crossProduct({B.x - A.x, B.y - A.y, B.z - A.z}, { C.x - A.x, C.y - A.y, C.z - A.z } );

        return (dotProduct(c1, normal) >= 0 && dotProduct(c2, normal) >= 0 && dotProduct(c3, normal) >= 0) ||
               (dotProduct(c1, normal) <= 0 && dotProduct(c2, normal) <= 0 && dotProduct(c3, normal) <= 0);
    }
};

struct Limits
{
    float x_min;
    float x_max;
    float y_min;
    float y_max;

    Limits limit(const Point& A, const Point& B, const Point& C)
    {
        Limits l;
        l.x_min = std::floor(std::min(A.x, B.x, C.x));
        l.x_max = std::ceil(std::max(A.x, B.x, C.x));

        l.y_min = std::floor(std::min(A.y, B.y, C.y));
        l.y_max = std::ceil(std::max(A.y, B.y, C.y));

        return l;
    }
};

struct Grid
{
    int heigth, width;

    int getIndex(int raw, int col) const
    {
        return raw * width + col;
    }

    //int getPixelsNumber(int heigth, int width) const
    //{
    //    return heigth * width;
    //}

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
    static void FloodFill(Grid& tab, size_t index)
    {
        std::deque<int> indexVect;
        indexVect.push_back(index); //indice de départ 

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

            if (raw != tab.heigth - 1)
                indexVect.push_back(tab.getIndex(raw + 1, col));

            if (col != 0)
                indexVect.push_back(tab.getIndex(raw, col - 1));

            if (col != tab.width - 1)
                indexVect.push_back(tab.getIndex(raw, col + 1));
        }
    }
};

// To add
//for (int y = y_min; y <= y_max; y++) {
//    for (int x = x_min; x <= x_max; x++) {
//        Point P = { x + 0.5, y + 0.5 }; // centre du pixel
//        if (pointInTriangle(P, A, B, C)) {
//            // Ce pixel fait partie du triangle
//            grid[y][x] = true;
//        }
//    }
//}
