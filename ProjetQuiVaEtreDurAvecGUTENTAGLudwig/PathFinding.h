#pragma once
#include <array>
#include <vector>
#include <iostream>
template<size_t height = 1, size_t width = height>
struct Dimension2d
{
	static_assert(height > 0 && width > 0, "must be at least a 1 by 1 grid");
	static constexpr size_t size_v = height * width;
	static constexpr size_t height_v = height;
	static constexpr size_t width_v = width;
	static size_t GetIndex(size_t row, size_t col);
	static bool IsInRange(size_t row, size_t col);
};

template <size_t height, size_t width>
size_t Dimension2d<height, width>::GetIndex(size_t row, size_t col)
{
	return row * width + col;
}

template <size_t height, size_t width>
bool Dimension2d<height, width>::IsInRange(size_t row, size_t col)
{
	if (row < 0 || row >= height)
		return false;
	if (col < 0 || col >= width)
		return false;
	return true;
}

template<typename tabType, size_t height = 1, size_t width = height>
struct Grid2d
{
	using dimention_type = Dimension2d<height, width>;

	Grid2d() = default;
	~Grid2d() = default;
	Grid2d(const Grid2d&) = default;
	Grid2d(Grid2d&&) = default;
	Grid2d(std::array<tabType, dimention_type::size_v> tab);
	Grid2d(const  tabType tab[dimention_type::size_v]);

	Grid2d& operator=(const Grid2d&) = default;
	Grid2d& operator=(Grid2d&&) = default;
	Grid2d& operator=(std::array<tabType, dimention_type::size_v> tab);
	Grid2d& operator=(const  tabType tab[dimention_type::size_v]);

	tabType& operator[](size_t index);
	const tabType& operator[](size_t index) const;
	tabType& At(size_t index);
	const tabType& At(size_t index) const;

	void DrawGrid() const;

private:
	std::array<tabType, dimention_type::size_v> m_data;
};



template <typename tabType, size_t height, size_t width>
Grid2d<tabType, height, width>::Grid2d(const tabType tab[dimention_type::size_v]): m_data()
{
	for (size_t i = 0; i < dimention_type::size_v; ++i)
	{
		m_data[i] = tab[i];
	}
}


template <typename tabType, size_t height, size_t width>
Grid2d<tabType, height, width>& Grid2d<tabType, height, width>::operator=(
	std::array<tabType, Dimension2d<height, width>::size_v> tab)
{
	m_data = tab;
	return *this;
}

template <typename tabType, size_t height, size_t width>
Grid2d<tabType, height, width>& Grid2d<tabType, height, width>::operator=(const tabType tab[dimention_type::size_v])
{
	for (size_t i = 0; i < dimention_type::size_v; ++i)
	{
		m_data[i] = tab[i];
	}
	return *this;
}

template <typename tabType, size_t height, size_t width>
tabType& Grid2d<tabType, height, width>::operator[](size_t index)
{
	return m_data[index];
}

template <typename tabType, size_t height, size_t width>
const tabType& Grid2d<tabType, height, width>::operator[](size_t index) const
{
	return m_data[index];
}

template <typename tabType, size_t height, size_t width>
tabType& Grid2d<tabType, height, width>::At(size_t index)
{
	return m_data.at(index);
}

template <typename tabType, size_t height, size_t width>
const tabType& Grid2d<tabType, height, width>::At(size_t index) const
{
	return m_data.at(index);
}

template <typename tabType, size_t height, size_t width>
void Grid2d<tabType, height, width>::DrawGrid() const
{
	for (int i = 0; i < height; ++i)
	{
		for (auto j = 0; j < width; ++j)
		{
			std::cout << m_data[i * width + j] << " ";
		}
		std::cout << "\n";
	}
}

template <typename tabType, size_t height, size_t width>
Grid2d<tabType, height, width>::Grid2d(std::array<tabType, Dimension2d<height, width>::size_v> tab): m_data(tab)
{
}

template<typename tabType, size_t height, size_t width = height>
struct FloodFill
{
	template<bool (*ModifyFN)(const tabType& value), void (*AffectationFN)(tabType& value)>
	static void Recursive(Grid2d<tabType, height, width>& tab, size_t index)
	{
		if (!ModifyFN(tab[index]))
			return;
		AffectationFN(tab[index]);
		size_t raw = index / width;
		size_t col = index - raw * width;
		if (Dimension2d<height, width>::IsInRange(raw - 1, col))
			Recursive<ModifyFN, AffectationFN>(tab, Dimension2d<height, width>::GetIndex(raw - 1, col));
		if (Dimension2d<height, width>::IsInRange(raw + 1, col))
			Recursive<ModifyFN, AffectationFN>(tab, Dimension2d<height, width>::GetIndex(raw + 1, col));
		if (Dimension2d<height, width>::IsInRange(raw, col - 1))
			Recursive<ModifyFN, AffectationFN>(tab, Dimension2d<height, width>::GetIndex(raw, col - 1));
		if (Dimension2d<height, width>::IsInRange(raw, col + 1))
			Recursive<ModifyFN, AffectationFN>(tab, Dimension2d<height, width>::GetIndex(raw, col + 1));
	}
	template<bool (*ModifyFN)(const tabType& value), void (*AffectationFN)(tabType& value)>
	static void Iterative(Grid2d<tabType, height, width>& tab, size_t index)
	{
		std::vector<size_t> toVisit;
		toVisit.push_back(index);

		size_t currentIndex = 0;
		while (!toVisit.empty())
		{
			currentIndex = toVisit.front();

			toVisit.erase(toVisit.begin());

			if (!ModifyFN(tab[currentIndex]))
				continue;
			AffectationFN(tab[currentIndex]);
			size_t raw = currentIndex / width;
			size_t col = currentIndex - raw * width;
			if (raw != 0)
				toVisit.push_back(Dimension2d<height, width>::GetIndex(raw - 1, col));
			if (raw != height - 1)
				toVisit.push_back(Dimension2d<height, width>::GetIndex(raw + 1, col));
			if (col != 0)
				toVisit.push_back(Dimension2d<height, width>::GetIndex(raw, col - 1));
			if (col != width - 1)
				toVisit.push_back(Dimension2d<height, width>::GetIndex(raw, col + 1));
		}
	}



};
