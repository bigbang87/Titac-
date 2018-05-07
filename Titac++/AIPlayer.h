#pragma once

#include "Player.h"
#include "BasicAI.h"
#include <memory>
class GameMap;

class AIPlayer : public Player
{
public:
	AIPlayer(const unsigned int id, GameMap const * const gameMapPtr);
	bool isAI() const override;
	virtual sf::Vector2i makeMove() const override;
	void getClickInput(const unsigned int x, const unsigned int y) override {};

private:
	std::unique_ptr<BasicAI> m_basicAI;
	GameMap const * const m_gameMapPtr;
};