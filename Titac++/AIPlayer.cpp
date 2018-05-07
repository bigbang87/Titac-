#include "AIPlayer.h"
#include "GameMap.h"

AIPlayer::AIPlayer(const unsigned int id, GameMap const * const gameMapPtr) : Player(id), m_gameMapPtr(gameMapPtr)
{
	m_basicAI = std::make_unique<BasicAI>(m_gameMapPtr->getMap());
}

bool AIPlayer::isAI() const
{
	return true;
}

sf::Vector2i AIPlayer::makeMove() const
{
	return sf::Vector2i(0, 0);
}