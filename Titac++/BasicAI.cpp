#include "BasicAI.h"
#include "GameMap.h"

BasicAI::BasicAI(const unsigned int myID, GameMap const * const gameMapPtr) : m_gameMapPtr(gameMapPtr), m_myID(myID)
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
	minimax(m_gameMapPtr->getCurrentPlayer(), state_ptr);
}

BasicAI::Move BasicAI::minimax(const unsigned int player, GenericGrid<int> const * const state_ptr)
{
	std::vector<int> moves = getMovesFromState(state_ptr);
	std::vector<Move> scoreList;
	scoreList.reserve(moves.size());
	unsigned int playersCount = m_gameMapPtr->getPlayersCount();
	for (std::size_t i = 0; i < moves.size(); ++i)
	{
		//sanity check
		++m_minimaxCalls;
		assert(m_minimaxCalls != 100 && "Minimax calls reached the limit");

		GenericGrid<int> changedState = *state_ptr;
		int x = 0;
		int y = 0;
		changedState.getPoint(moves[i], x, y);
		changedState[moves[i]] = player;
		sf::Vector2i newMove(x, y);

		//check win
		if (m_gameMapPtr->checkWin(newMove, &changedState))
		{
			Move scoreMove;
			scoreMove.moveIndex = moves[i];
			if (player == m_myID)
				scoreMove.score = 10;
			else
				scoreMove.score = -10;
			return scoreMove;
		}
		else
		{
			//if not terminal state
			if (moves.size() > 1)
			{
				//
				// FIX ERROR HERE, IT PROVIDE WRONG PLAYER WITH ID == 0
				//
				//manage players
				unsigned int nextPlayer = player;
				++nextPlayer;
				nextPlayer = nextPlayer == playersCount ? 0 : nextPlayer;
				//call minimax for deeper state
				Move scoreMove = minimax(nextPlayer, &changedState);
				scoreList.push_back(scoreMove);
			}
		}
	}

	Move bestScoreMove;
	for (auto &scoreMove : scoreList)
	{
		if (player == m_myID)
		{
			if (scoreMove.score > bestScoreMove.score)
				bestScoreMove = scoreMove;
		}
		else
		{
			if (scoreMove.score < bestScoreMove.score)
				bestScoreMove = scoreMove;
		}
	}
	std::cout << "size of moves vector: " << moves.size() << "\n";
	return bestScoreMove;
}