#pragma once

#include <SFML/Graphics.hpp>

class GameDelegate
{
private:
	sf::Vector2u m_originalResolution;
	sf::Vector2u m_resolution;
	sf::RenderWindow& m_window;
public:
	GameDelegate() = delete;
	GameDelegate(sf::RenderWindow& renderWindow);
	void setResolution(sf::Vector2u);
	const sf::Vector2u getResolution();
	const sf::Vector2u getOriginalResolution();
};