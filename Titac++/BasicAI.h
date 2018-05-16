#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "GenericGrid.h"

class BasicAI
{
public:
	BasicAI();
	std::vector<int> getMovesFromState(GenericGrid<int> const * const state_ptr);
	void initiateMove(GenericGrid<int> const * const state_ptr);
	int minimax(GenericGrid<int> const * const state_ptr);
};