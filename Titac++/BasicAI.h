#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "GenericGrid.h"

class BasicAI
{
public:
	BasicAI() = delete;
	BasicAI(GenericGrid<int> const* state_ptr);
	std::vector<int> getMovesFromState(std::vector<int> state);
	void initiateMove(GenericGrid<int> const * const state_ptr);
	int minimax(std::vector<int> state);
};