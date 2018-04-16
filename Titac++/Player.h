#pragma once

#include "Actor.h"
#include "SFML\Graphics.hpp"

class Player : public Actor
{
public:
	Player(const unsigned int id) : m_playerID(id) {};
	virtual sf::Vector2i makeMove() const = 0;

private:
	const unsigned int m_playerID;
};