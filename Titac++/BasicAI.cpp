#include "BasicAI.h"

BasicAI::BasicAI(GenericGrid<int> const* state_ptr)
{
	getMovesFromState(state_ptr);
}

std::unique_ptr<std::vector<int>> BasicAI::getMovesFromState(GenericGrid<int> const * const state_ptr)
{
	std::unique_ptr<std::vector<int>> possibleMoves = std::make_unique<std::vector<int>>();
	possibleMoves.get()->resize(state_ptr->getSize());
	unsigned int emptySpaces = 0;
	for (std::size_t i = 0; i < state_ptr->getSize(); ++i)
	{
		if (state_ptr->getValueFromIndex(i) == 0)
			std::cout << i;
	}
	/*
	for (GenericGrid<int>::ConstIterator i = state_ptr->begin(); i != state_ptr->end(); ++i)
		if (*i == 0)
	*/
	std::cout << possibleMoves.get()->size() << "\n";
	return possibleMoves;
}