#include "GameDelegate.h"
#include <iostream>

GameDelegate::GameDelegate(sf::RenderWindow& renderWindow) : m_window(renderWindow)
{
	m_originalResolution = renderWindow.getSize();
	m_resolution = renderWindow.getSize();
}

void GameDelegate::setResolution(sf::Vector2u& resolution)
{
	m_resolution = resolution;
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

const sf::Vector2u GameDelegate::getFixedRatioResolution(const unsigned int x, const unsigned int y)
{
	float newRatio = 0;
	float widthRatio = 0;
	sf::Vector2u res;
	if (m_resolution.y != y)
	{
		newRatio = (float)m_originalResolution.y / y;
		widthRatio = (float)m_originalResolution.x / newRatio;
		res = sf::Vector2u(widthRatio, y);
		return res;
	}
	if (m_resolution.x != x)
	{
		newRatio = (float)m_originalResolution.x / x;
		widthRatio = (float)m_originalResolution.y / newRatio;
		res = sf::Vector2u(x, widthRatio);
		return res;
	}
	return sf::Vector2u(x, y);
}
