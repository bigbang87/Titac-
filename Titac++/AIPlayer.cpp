#include "AIPlayer.h"
#include "GameMap.h"

AIPlayer::AIPlayer(const unsigned int id, GameMap const * const gameMapPtr) : Player(id), m_gameMapPtr(gameMapPtr)
{
}

bool AIPlayer::isAI() const
{
	return true;
}

sf::Vector2i AIPlayer::makeMove() const
{
	m_basicAI->getMovesFromState(m_gameMapPtr->getMap());
	return sf::Vector2i(0, 0);
}