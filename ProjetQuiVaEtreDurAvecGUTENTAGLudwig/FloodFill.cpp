#include "FloodFill.h"

Dimension2d::Dimension2d(size_t height_, size_t width_): width(width_), height(height_)
{}



size_t Dimension2d::GetIndex(size_t row, size_t col) const
{
	return row * width + col;
}

bool Dimension2d::IsInRange(size_t row, size_t col) const
{
	if (row < 0 || row >= height)
		return false;
	if (col < 0 || col >= width)
		return false;
	return true;
}

size_t Dimension2d::Size() const
{
	return width * height;
}
