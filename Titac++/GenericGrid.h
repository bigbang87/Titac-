#pragma once

#include <vector>

template <typename T>
class GenericGrid
{
public:
	GenericGrid(std::size_t sizeX, std::size_t sizeY)
	{
		m_sizeX = sizeX;
		m_sizeY = sizeY;
		grid.resize(sizeX * sizeY);
	}
	
	const std::size_t getSizeX()
	{
		return m_sizeX;
	}

	const std::size_t getSizeY()
	{
		return m_sizeY;
	}

	T getElement(unsigned int x, unsigned int y)
	{
		//TODO getting the element
		return grid[0];
	}

	bool setElement(unsigned int x, unsigned int y, T element)
	{
		//TODO getting the element
		grid[x * y] = element;
	}

private:
	std::size_t m_sizeX;
	std::size_t m_sizeY;
	std::vector<T> grid;
};