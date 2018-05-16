#include "BasicAI.h"

BasicAI::BasicAI()
{
	std::cout << "BasicAI player initialized \n";
}

std::vector<int> BasicAI::getMovesFromState(GenericGrid<int> const * const state_ptr)
{
	std::vector<int> possibleMoves;
	possibleMoves.reserve(state_ptr->getSize());
	for (GenericGrid<int>::ConstIterator i = state_ptr->begin(); i != state_ptr->end(); ++i)
		if (*i == 0)
			possibleMoves.push_back(*i);

	return possibleMoves;
}

void BasicAI::initiateMove(GenericGrid<int> const * const state_ptr)
{
	minimax(state_ptr);
}

int BasicAI::minimax(GenericGrid<int> const * const state_ptr)
{
	std::vector<int> moves = getMovesFromState(state_ptr);
	for (std::size_t i = 0; i < moves.size(); ++i)
	{
		std::cout << moves[i] << ", ";
	}
	std::cout << "size of moves vector: " << moves.size() << "\n";
	return 0;
}