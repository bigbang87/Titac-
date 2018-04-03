#include "GameMap.h"
#include "Scene.h"
#include <iostream>

GameMap::GameMap(const unsigned int sizeX, const unsigned int sizeY, Scene* scene) : m_scenePtr(scene)
{
	m_map.resize(sizeX);
	for (int i = 0; i < sizeY; ++i)
		m_map[i].resize(sizeY);
	m_size = sf::Vector2u(sizeX, sizeY);
	for (int x = 0; x < sizeX; ++x) {
		for (int y = 0; y < sizeY; ++y)
		{
			makeTile(x, y);
		}
	}
	std::cout << "GameMap created with size of " << sizeX << " x " << sizeY << "\n";
}

const sf::Vector2u GameMap::getSize()
{
	return m_size;
}

void GameMap::makeTile(unsigned int x, unsigned int y)
{
	unsigned int tileSize = 64;
	int topMargin = 100;
	int spacing = 15;
	sf::Vector2u res = m_scenePtr->getGameDelegate().getResolution();
	int tableSize = (int)((m_size.x * tileSize) + (m_size.x * spacing));
	int centringOffset = (int)((res.x - tableSize) * 0.5f) + (int)(spacing * 0.5f);
	int posX = (x * tileSize) + (x * spacing) + centringOffset;
	int posY = (y * tileSize) + (y * spacing) + topMargin;
	std::unique_ptr<UIButton> tilePtr = std::make_unique<UIButton>(sf::IntRect(posX, posY, tileSize, tileSize),
		"defaultMapTile.png", "hoverMapTile.png", "pressedMapTile.png");
	tilePtr->addListener([this, x, y]() {this->onClick(x, y); });
	m_scenePtr->getCanvas()->addElement(std::move(tilePtr));
}

void GameMap::onClick(unsigned int x, unsigned int y)
{
	std::cout << "Clicked tile: [" << x << "][" << y << "]\n";
}
