#include "GameMap.h"
#include "Scene.h"
#include <iostream>

GameMap::GameMap(const unsigned int sizeX, const unsigned int sizeY, Scene* scene) : m_scenePtr(scene)
{
	m_grid = std::make_unique<GenericGrid<int>>(sizeX, sizeY);
	for (unsigned int y = 0; y < sizeY; ++y) {
		for (unsigned int x = 0; x < sizeX; ++x)
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

	addPlayers(this);
}

void GameMap::humanInput(const unsigned int x, const unsigned int y)
{
	Player* const player_ptr = m_players.at(m_currentPlayer).get();
	player_ptr->getClickInput(x, y);
	processPlayersMove();
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
	btnPtr->addListener([this, x, y]() {this->humanInput(x, y); });
	m_scenePtr->getCanvas()->addElement(std::move(btnPtr));
	//adding images
	std::unique_ptr<UIImage> imagePtr = std::make_unique<UIImage>(sf::IntRect(posX, posY, tileSize, tileSize), "emptyFigure.png");
	m_images.push_back(imagePtr.get());
	m_scenePtr->getCanvas()->addElement(std::move(imagePtr));
}

bool GameMap::checkWin(GenericGrid<int> const * const state) const
{
	const unsigned int player = m_currentPlayer;
	const unsigned int winSize = 3;
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
					canMoveA = checkPoint(aPoint - dir, player, state);
					if (canMoveA)
					{
						aPoint -= dir;
						++points;
					}
				}
				if (canMoveB)
				{
					canMoveB = checkPoint(bPoint + dir, player, state);
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

bool GameMap::cellInBounds(const sf::Vector2i cell, GenericGrid<int> const * const state) const
{
	return !(cell.x < 0 || cell.y < 0 || 
		(unsigned int)cell.x >= state->getSizeX() || (unsigned int)cell.y >= state->getSizeY());
}

bool GameMap::checkPoint(const sf::Vector2i point, const unsigned int player, GenericGrid<int> const * const state) const
{
	if (cellInBounds(point, state))
	{
		const int cellValue = state->at(point.x, point.y);
		return cellValue == player;
	}
	return false;
}

void GameMap::addPlayers(const GameMap* gameMapPtr)
{
	m_currentPlayer = 0;
	m_players.push_back(std::make_unique<HumanPlayer>(1));
	m_players.push_back(std::make_unique<AIPlayer>(2, gameMapPtr));
}

void GameMap::processPlayersMove()
{
	const Player* player_ptr = m_players.at(m_currentPlayer).get();
	sf::Vector2i pos = player_ptr->makeMove();
	onMove(pos.x, pos.y, player_ptr->getPlayerID());
	++m_currentPlayer;
	m_currentPlayer = m_currentPlayer == m_players.size() ? 0 : m_currentPlayer;
	//tick for next AI
	player_ptr = m_players.at(m_currentPlayer).get();
	if (!player_ptr->isAI())
		return;
	processPlayersMove();
}

GenericGrid<int> const*  GameMap::getMap() const
{
	return m_grid.get();
}

void GameMap::onMove(const unsigned int x, const unsigned int y, const unsigned int playerID)
{
	int& tileValue = m_grid->at(x, y);
	if (tileValue != 0)
		return;
	tileValue = playerID;
	const int imgPos = m_grid->getIdx(x, y);
	UIImage* imgPtr = m_images.at(imgPos);
	std::string path = m_figuresMap.at(tileValue);
	imgPtr->setSprite(path);
	std::cout << "Clicked tile: [" << x << "][" << y << "] = " << m_grid->at(x, y) << "\n";
	if (checkWin(sf::Vector2i(x, y), m_grid.get()))
		std::cout << "Player number " << tileValue << " won the game\n";
}