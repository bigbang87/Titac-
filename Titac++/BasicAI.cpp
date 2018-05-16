#include "BasicAI.h"
#include "GameMap.h"

BasicAI::BasicAI(GameMap const * const gameMapPtr) : m_gameMapPtr(gameMapPtr)
{
	std::cout << "BasicAI player initialized \n";
	m_minimaxCalls = 0;
}

std::vector<int> BasicAI::getMovesFromState(GenericGrid<int> const * const state_ptr)
{
	std::vector<int> possibleMoves;
	possibleMoves.reserve(state_ptr->getSize());
	for (GenericGrid<int>::ConstIterator i = state_ptr->begin(); i != state_ptr->end(); ++i)
		if (*i == 0)
			possibleMoves.push_back(i.getIndex());
	return possibleMoves;
}

void BasicAI::initiateMove(GenericGrid<int> const * const state_ptr)
{
	minimax(state_ptr);
}

int BasicAI::minimax(GenericGrid<int> const * const state_ptr)
{
	std::vector<int> moves = getMovesFromState(state_ptr);
	int score = -10000;
	for (std::size_t i = 0; i < moves.size(); ++i)
	{
		++m_minimaxCalls;
		if (m_minimaxCalls == 100)
		{
			std::cout << "Minimax calls reached the limit, exiting \n";
			return -1;
		}
		GenericGrid<int> changedState = *state_ptr;
		std::cout << moves[i] << ", ";
		if (m_gameMapPtr->checkWin(state_ptr))
		{
			return score;
		}
	}
	std::cout << "size of moves vector: " << moves.size() << "\n";
	return 0;
}