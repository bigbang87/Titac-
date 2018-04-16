#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(const unsigned int id);
	sf::Vector2i makeMove() const override;
};