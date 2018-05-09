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
	std::vector<int> getMovesFromState(GenericGrid<int> const * const state_ptr);
	int minimax();
};