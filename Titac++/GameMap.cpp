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

bool GameMap::checkWin(int& player)
{
	int winSize = 3;
	int points = 0;
	int currentPlayer = 0;
	//check lines
	for (int y = 0; y < m_grid->getSizeY(); ++y) {
		for (int x = 0; x < m_grid->getSizeX(); ++x)
		{
			const int cell = m_grid->at(x, y);
			bool win = checkCell(cell, currentPlayer, points, player, winSize);
			if (win)
				return true;
		}
	}
	return false;
}

bool GameMap::checkCell(const int& cell, int& currentPlayer, int& points, int& winPlayer, const int winSize)
{
	if (cell == 0)
	{
		points = 0;
		currentPlayer = 0;
		return false;
	}
	if (cell == currentPlayer)
	{
		++points;
	}
	else
	{
		currentPlayer = cell;
		points = 1;
		return false;
	}
	if (points == winSize)
	{
		winPlayer = currentPlayer;
		return true;
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
	int winner = 0;
	if (checkWin(winner))
		std::cout << "Plater number " << winner << " won the game\n";
}