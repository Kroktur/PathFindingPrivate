#pragma once
#include <vector>

struct Point
{
	float x, y, z;
};

struct Triangle
{
	Point A, B, C, G;

	void setSegment()
	{
		this -> A = { 0.0f, 0.0f };
		this-> B = { 1.0f, 1.0f };
		this-> C = { 0.0f, 2.0f };

		auto xG = (A.x + B.x + C.x) / 3;
		auto yG = (A.y + B.y + C.y) / 3;

		this-> G = { xG ,yG }; //center of the triangle

		Vec2 AB;
		AB.x = B.x - A.x;
		AB.y = B.y - A.y;

		Vec2 BC;
		BC.x = C.x - B.x;
		BC.y = C.y - B.y;

		Vec2 CA;
		CA.x = A.x - C.x;
		CA.y = A.y - C.y;

		Vec2 GCenter;
		GCenter.x = G.x - AB.x;
		GCenter.x = G.y - AB.y;

		auto startVec = A;
		auto dirVec = G;
	}
};

struct Square
{
	int m_height;

	Square(int value) : m_height(value)
	{ }

	float getSize()
	{
		return m_height * m_height;
	}
};

struct Grid
{
	int m_height, m_width;

	Grid(int value) : m_height(value), m_width(value)
	{ }

	std::vector<Square> tab;
};