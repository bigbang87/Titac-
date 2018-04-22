#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const unsigned int id) : Player(id)
{
}

sf::Vector2i HumanPlayer::makeMove() const
{
	return clickedPos;
}

bool HumanPlayer::isAI() const
{
	return false;
}

void HumanPlayer::getClickInput(const unsigned int x, const unsigned int y)
{
	clickedPos = sf::Vector2i(x, y);
}
