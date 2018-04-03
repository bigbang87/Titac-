#pragma once
#include "SFML\Graphics.hpp"
#include "Actor.h"
#include "UIButton.h"

class GameMap
{
public:
	GameMap(const unsigned int sizeX, const unsigned int sizeY, Scene* scene);
	const sf::Vector2u getSize();
	void onClick(unsigned int x, unsigned int y);

private:
	void makeTile(unsigned int x, unsigned int y);

private:
	sf::Vector2u m_size;
	std::vector<std::vector<int>> m_map;
	std::vector<UIButton> m_buttonTiles;
	Scene* m_scenePtr;
};