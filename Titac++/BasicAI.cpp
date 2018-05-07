#include "BasicAI.h"

BasicAI::BasicAI(GenericGrid<int> const* state_ptr)
{
	getMovesFromState(state_ptr);
}

std::vector<std::vector<int>>* BasicAI::getMovesFromState(GenericGrid<int> const * const state_ptr)
{
	for (GenericGrid<int>::ConstIterator i = state_ptr->begin(); i != state_ptr->end(); i++)
	{
		std::cout << *i << " ";
	}

	std::cout << "\n";
	return nullptr;
}