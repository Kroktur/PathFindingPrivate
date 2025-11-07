#pragma once
#include <vector>
#include <iostream>
#include <deque>
#include <cmath>

#pragma optimise ("", off)

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


struct Vec2
{
    float x, y;

    static Vec2 getVector(const Point& A, const Point& B)
    {
        return { B.x - A.x, B.y - A.y};
    }
};


Vec3 crossProduct(const Vec3& AB, const Vec3& AC)
{
    return { AB.y * AC.z - AB.z * AC.y,
             AB.z * AC.x - AB.x * AC.z,
             AB.x * AC.y - AB.y * AC.x, };
}

float crossProduct(const Point& A, const Point& B, const Point& C)
{
    Vec2 AB = Vec2::getVector(A, B);
    Vec2 AC = Vec2::getVector(A, C);

    return AB.x * AC.y - AB.y * AC.x;
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

    Triangle(Point a, Point b, Point c) : A(a), B(b), C(c)
    { }

    bool testPointTriangle(const Point& P) const
    {
        float test1 = crossProduct(A,B,P);
        float test2 = crossProduct(B,C,P);
        float test3 = crossProduct(C,A,P);

        return ((test1 >= 0 && test2 >= 0 && test3 >= 0) ||
                (test1 <= 0 && test2 <= 0 && test3 <= 0));
    }
};

struct Limits
{
    float x_min;
    float x_max;
    float y_min;
    float y_max;

    static Limits limit(const Triangle& tri)
    {
        Limits l;
        l.x_min = std::floor(std::min(std::min(tri.A.x, tri.B.x), tri.C.x));
        l.x_max = std::ceil(std::max(std::max(tri.A.x, tri.B.x), tri.C.x));

        l.y_min = std::floor(std::min(std::min(tri.A.y, tri.B.y), tri.C.y));
        l.y_max = std::ceil(std::max(std::max(tri.A.y, tri.B.y), tri.C.y));

        return l;
    }
};

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
                Point P = { static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f, 0};
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

#pragma optimise ("", on)
