#pragma once
#include "SFML\Graphics.hpp"
#include "Actor.h"
#include "UIButton.h"
#include  "GenericGrid.h"

class GameMap : public Actor
{
public:
	GameMap(const unsigned int sizeX, const unsigned int sizeY, Scene* scene);
	void onClick(unsigned int x, unsigned int y);

private:
	void makeTile(unsigned int x, unsigned int y);
	bool checkWin(const unsigned int player, const int x, const int y);
	const bool cellInBounds(const sf::Vector2i cell) const;
	const bool checkPoint(const sf::Vector2i point, const unsigned int player);

private:
	std::unique_ptr<GenericGrid<int>> m_grid;
	std::vector<UIImage*> m_images;
	Scene* m_scenePtr;
	std::map<int, std::string> m_figuresMap;
};