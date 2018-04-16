#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const unsigned int id) : Player(id)
{
}

sf::Vector2i HumanPlayer::makeMove() const
{
	return sf::Vector2i();
}
