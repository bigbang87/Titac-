#pragma once

#include "Actor.h"
#include "SFML\Graphics.hpp"

class Player : public Actor
{
public:
	Player(const unsigned int id) : m_playerID(id) {};
	virtual sf::Vector2i makeMove() const = 0;
	virtual bool isAI() const = 0;
	virtual unsigned int getPlayerID() const { return m_playerID; };
	virtual void getClickInput(const unsigned int x, const unsigned int y) = 0;

protected:
	const unsigned int m_playerID;
};