#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(const unsigned int id);
	sf::Vector2i makeMove() const override;
	bool isAI() const override;
	void getClickInput(const unsigned int x, const unsigned int y) override;

private:
	sf::Vector2i clickedPos;
};