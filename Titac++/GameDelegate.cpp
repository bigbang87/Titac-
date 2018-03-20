#include "GameDelegate.h"
#include <iostream>

GameDelegate::GameDelegate(sf::RenderWindow& renderWindow) : m_window(renderWindow)
{
}

void GameDelegate::setResoluationFromCursor()
{
	const sf::Vector2i pos = m_window.getPosition();
	const sf::Vector2i size = sf::Mouse::getPosition();
	sf::Vector2u newSize(600, 600);
	m_window.setSize(newSize);
	std::cout << "GameDelegate: " <<  newSize.x << ", " << newSize.y << "\n";
}
