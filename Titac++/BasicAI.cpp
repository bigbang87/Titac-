#include "BasicAI.h"

BasicAI::BasicAI(GenericGrid<int> const* state_ptr)
{
}

std::vector<int> BasicAI::getMovesFromState(std::vector<int> state)
{
	std::vector<int> possibleMoves;
	possibleMoves.reserve(state.size());
	for (std::size_t i = 0; i < state.size(); ++i)
	{
		if (state[i] == 0)
			possibleMoves.push_back(i);
	}
	/*
	for (GenericGrid<int>::ConstIterator i = state_ptr->begin(); i != state_ptr->end(); ++i)
		if (*i == 0)
	*/
	return possibleMoves;
}

void BasicAI::initiateMove(GenericGrid<int> const * const state_ptr)
{
	minimax(state_ptr->getCopyOfData());
}

int BasicAI::minimax(std::vector<int> state)
{
	std::vector<int> moves = getMovesFromState(state);
	for (std::size_t i = 0; i < moves.size(); ++i)
	{
		std::cout << moves[i] << ", ";
	}
	std::cout << "size of moves vector: " << moves.size() << "\n";
	return 0;
}