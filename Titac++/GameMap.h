#pragma once
#include "SFML\Graphics.hpp"
#include "Actor.h"
#include "UIButton.h"
#include  "GenericGrid.h"

class GameMap
{
public:
	GameMap(const unsigned int sizeX, const unsigned int sizeY, Scene* scene);
	void onClick(unsigned int x, unsigned int y);

private:
	void makeTile(unsigned int x, unsigned int y);

private:
	std::unique_ptr<GenericGrid<int>> m_grid;
	std::vector<UIButton> m_buttonTiles;
	Scene* m_scenePtr;
};