#pragma once
#include "SFML\Graphics.hpp"
#include "Actor.h"
#include "UIButton.h"
#include "GenericGrid.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

class GameMap : public Actor
{
public:
	GameMap(const unsigned int sizeX, const unsigned int sizeY, Scene* scene);
	void humanInput(const unsigned int x, const unsigned int y);
	void onMove(const unsigned int x, const unsigned int y, const unsigned int playerID);
	GenericGrid<int> const* getMap() const;

private:
	void makeTile(unsigned int x, unsigned int y);
	bool checkWin(const sf::Vector2i point) const;
	bool cellInBounds(const sf::Vector2i cell) const;
	bool checkPoint(const sf::Vector2i point, const unsigned int player) const;
	void addPlayers(const GameMap* gameMapPtr);
	void processPlayersMove();

private:
	std::unique_ptr<GenericGrid<int>> m_grid;
	std::vector<UIImage*> m_images;
	Scene* m_scenePtr;
	std::map<int, std::string> m_figuresMap;
	std::vector<std::unique_ptr<Player>> m_players;
	unsigned int m_currentPlayer;
};