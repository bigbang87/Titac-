#include "GameDelegate.h"
#include <iostream>

GameDelegate::GameDelegate(sf::RenderWindow& renderWindow) : m_window(renderWindow)
{
	m_originalResolution = renderWindow.getSize();
	m_resolution = renderWindow.getSize();
}

void GameDelegate::setResolution(sf::Vector2u resolution)
{
	m_window.setSize(resolution);
	std::cout << "GameDelegate: " << resolution.x << ", " << resolution.y << "\n";
}

const sf::Vector2u GameDelegate::getResolution()
{
	return m_resolution;
}

const sf::Vector2u GameDelegate::getOriginalResolution()
{
	return m_originalResolution;
}
