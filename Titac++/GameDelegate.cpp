#include "GameDelegate.h"
#include <iostream>

GameDelegate::GameDelegate(sf::RenderWindow& renderWindow) : m_window(renderWindow)
{
}

void GameDelegate::setResoluationFromCursor()
{
	const sf::Vector2i pos = m_window.getPosition();
	const sf::Vector2i size = sf::Mouse::getPosition();
	sf::Vector2u newSize(pos.x + size.x, pos.y + size.y);
	m_window.setSize(newSize);
	//std::cout << newSize.x << ", " << newSize.y << "\n";
}
