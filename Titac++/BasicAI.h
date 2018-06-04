#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "GenericGrid.h"
#include "SFML/Graphics.hpp"
class GameMap;

class BasicAI
{
	struct Move {
		int score;
		int moveIndex;
		int callID;
		int parentCall;
	};

public:
	BasicAI() = delete;
	BasicAI(const unsigned int myID, GameMap const * const gameMapPtr);
	std::vector<int> getMovesFromState(GenericGrid<int> const * const state_ptr);
	sf::Vector2i initiateMove(GenericGrid<int> const * const state_ptr);
	Move minimax(const int callParent, const unsigned int player, int parentMove, 
		GenericGrid<int> const * const state_ptr);

private:
	unsigned int m_minimaxCalls;
	const unsigned int m_myID;
	GameMap const * const m_gameMapPtr;
};