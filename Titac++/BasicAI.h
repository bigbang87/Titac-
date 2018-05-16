#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "GenericGrid.h"
class GameMap;

class BasicAI
{
public:
	BasicAI() = delete;
	BasicAI(GameMap const * const gameMapPtr);
	std::vector<int> getMovesFromState(GenericGrid<int> const * const state_ptr);
	void initiateMove(GenericGrid<int> const * const state_ptr);
	int minimax(GenericGrid<int> const * const state_ptr);

private:
	unsigned int m_minimaxCalls;
	GameMap const * const m_gameMapPtr;
};