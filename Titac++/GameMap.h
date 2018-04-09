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

private:
	std::unique_ptr<GenericGrid<int>> m_grid;
	std::vector<UIImage*> m_images;
	Scene* m_scenePtr;
	std::map<int, std::string> m_figuresMap
	{
		{ 0, "emptyFigure.png" },
		{ 1, "banana.png" },
		{ 2, "apple.png" },
		{ 3, "cherry.png" },
		{ 4, "strawberry.png" }
	};
};