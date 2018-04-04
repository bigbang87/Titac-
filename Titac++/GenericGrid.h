#pragma once

#include <vector>
#include "SFML/Graphics.hpp"

template <typename T>
class GenericGrid
{
public:
	GenericGrid(unsigned int sizeX, unsigned int sizeY)
	{
		m_size = sf::Vector2u(sizeX, sizeY);
		grid.resize(sizeX * sizeY);
	}
	
	const sf::Vector2u getSize()
	{
		return m_size;
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
	sf::Vector2u m_size;
	std::vector<T> grid;
};