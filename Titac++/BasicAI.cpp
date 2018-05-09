#include "BasicAI.h"

BasicAI::BasicAI(GenericGrid<int> const* state_ptr)
{
	getMovesFromState(state_ptr);
}

std::vector<int> BasicAI::getMovesFromState(GenericGrid<int> const * const state_ptr)
{
	std::vector<int> possibleMoves;
	possibleMoves.reserve(state_ptr->getSize());
	unsigned int emptySpaces = 0;
	for (std::size_t i = 0; i < state_ptr->getSize(); ++i)
	{
		if ((*state_ptr)[i] == 0)
			possibleMoves.push_back(i);
	}
	/*
	for (GenericGrid<int>::ConstIterator i = state_ptr->begin(); i != state_ptr->end(); ++i)
		if (*i == 0)
	*/
	std::cout << possibleMoves.size() << "\n";
	return possibleMoves;
}