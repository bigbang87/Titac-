#include "GameMap.h"
#include "Scene.h"
#include <iostream>

GameMap::GameMap(const unsigned int sizeX, const unsigned int sizeY, Scene* scene) : m_scenePtr(scene)
{
	m_grid = std::make_unique<GenericGrid<int>>(sizeX, sizeY);
	/*for (GenericGrid<int>::Iterator i = m_grid->begin(); i != m_grid->end(); i++)
		std::cout << *i << " ";*/
	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x)
		{
			makeTile(x, y);
			m_grid->at(x, y) = 0;
		}
	}
	m_figuresMap = {
	{ 0, "emptyFigure.png" },
	{ 1, "banana.png" },
	{ 2, "apple.png" },
	{ 3, "cherry.png" },
	{ 4, "strawberry.png" }	};
	std::cout << "GameMap created with size of " << sizeX << " x " << sizeY << "\n";
}

void GameMap::makeTile(unsigned int x, unsigned int y)
{
	//calculating positions
	unsigned int tileSize = 64;
	int topMargin = 100;
	int spacing = 15;
	sf::Vector2u res = m_scenePtr->getGameDelegate().getResolution();
	std::size_t sizeX = m_grid->getSizeX();
	int tableSize = (int)((sizeX * tileSize) + (sizeX * spacing));
	int centringOffset = (int)((res.x - tableSize) * 0.5f) + (int)(spacing * 0.5f);
	int posX = (x * tileSize) + (x * spacing) + centringOffset;
	int posY = (y * tileSize) + (y * spacing) + topMargin;
	//adding button
	std::unique_ptr<UIButton> btnPtr = std::make_unique<UIButton>(sf::IntRect(posX, posY, tileSize, tileSize),
		"defaultMapTile.png", "hoverMapTile.png", "pressedMapTile.png");
	btnPtr->addListener([this, x, y]() {this->onClick(x, y); });
	m_scenePtr->getCanvas()->addElement(std::move(btnPtr));
	//adding images
	std::unique_ptr<UIImage> imagePtr = std::make_unique<UIImage>(sf::IntRect(posX, posY, tileSize, tileSize), "emptyFigure.png");
	m_images.push_back(imagePtr.get());
	m_scenePtr->getCanvas()->addElement(std::move(imagePtr));
}

bool GameMap::checkWin(const sf::Vector2i point) const
{
	const unsigned int player = m_grid->at(point.x, point.y);
	const unsigned int winSize = 4;
	for (int x = -1; x <= 1; ++x)
		for (int y = -1; y <= 1; ++y)
		{
			if (x == 0 && y == 0)
				continue;

			unsigned int points = 1;
			sf::Vector2i aPoint = point;
			sf::Vector2i bPoint = point;
			bool canMoveA = true;
			bool canMoveB = true;
			sf::Vector2i dir(x, y);
			for (int i = 0; i < winSize; ++i)
			{
				if (canMoveA)
				{
					canMoveA = checkPoint(aPoint - dir, player);
					if (canMoveA)
					{
						aPoint -= dir;
						++points;
					}
				}
				if (canMoveB)
				{
					canMoveB = checkPoint(bPoint + dir, player);
					if (canMoveB)
					{
						bPoint += dir;
						++points;
					}
				}

				if (points >= winSize)
					return true;
				if (!canMoveA && !canMoveB)
					break;
			}
		}

	return false;
}

bool GameMap::cellInBounds(const sf::Vector2i cell) const
{
	return !(cell.x < 0 || cell.y < 0 || cell.x >= m_grid->getSizeX() || cell.y >= m_grid->getSizeY());
}

bool GameMap::checkPoint(const sf::Vector2i point, const unsigned int player) const
{
	if (cellInBounds(point))
	{
		const int cellValue = m_grid->at(point.x, point.y);
		return cellValue == player;
	}
	return false;
}

void GameMap::onClick(unsigned int x, unsigned int y)
{
	int& getValue = m_grid->at(x, y);
	++getValue;
	getValue = (getValue == m_figuresMap.size()) ? 0 : getValue;
	const int imgPos = m_grid->getIdx(x, y);
	UIImage* imgPtr = m_images.at(imgPos);
	std::string path = m_figuresMap.at(getValue);
	imgPtr->setSprite(path);
	std::cout << "Clicked tile: [" << x << "][" << y << "] = " << m_grid->at(x, y) << "\n";
	if (checkWin(sf::Vector2i(x, y)))
		std::cout << "Plater number " << getValue << " won the game\n";
}