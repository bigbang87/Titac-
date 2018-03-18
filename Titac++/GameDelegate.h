#pragma once

#include <SFML/Graphics.hpp>

class GameDelegate
{
private:
	sf::Vector2u m_windowSize;
	sf::RenderWindow& m_window;
public:
	GameDelegate() = delete;
	GameDelegate(sf::RenderWindow& renderWindow);
	void setResoluationFromCursor();
};