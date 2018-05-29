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

sf::Vector2i BasicAI::initiateMove(GenericGrid<int> const * const state_ptr)
{
	std::cout << "MINIMAX START \n";
	Move move =	minimax(m_gameMapPtr->getCurrentPlayerID(), state_ptr);
	int x, y;
	m_gameMapPtr->getMap()->getPoint(move.moveIndex, x, y);
	std::cout << "MINIMAX END \n";
	//m_gameMapPtr->getMap()->getPoint(8, x, y);
	//std::cout << "TEST: x " << x << ", y " << y << " at " << m_gameMapPtr->getMap()->at(x, y) << "\n";
	return sf::Vector2i(x, y);
	//return sf::Vector2i(1, 1);
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
		//assert(m_minimaxCalls != 10000 && "Minimax calls reached the limit");

		GenericGrid<int> changedState = *state_ptr;
		int x = 0;
		int y = 0;
		changedState.getPoint(moves[i], x, y);
		changedState[moves[i]] = player;
		sf::Vector2i newMove(x, y);

		//std::cout << "Call number " << m_minimaxCalls << " for player: " << player << "\n";
		//changedState.drawState();

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
				//manage players
				unsigned int nextPlayer = player;
				++nextPlayer;
				nextPlayer = nextPlayer > playersCount ? 1 : nextPlayer;
				//call minimax for deeper state
				Move scoreMove = minimax(nextPlayer, &changedState);
				scoreList.push_back(scoreMove);
			}
			else
			{
				Move scoreMove;
				scoreMove.moveIndex = moves[i];
				scoreMove.score = 0;
				scoreList.push_back(scoreMove);
			}
		}
	}

	Move bestScoreMove;
	if (player == m_myID)
	{
		bestScoreMove.score = -10000;
		for (auto &scoreMove : scoreList)
			if (scoreMove.score > bestScoreMove.score)
				bestScoreMove = scoreMove;
	}
	else
	{
		bestScoreMove.score = 10000;
		for (auto &scoreMove : scoreList)
			if (scoreMove.score < bestScoreMove.score)
				bestScoreMove = scoreMove;
	}
	return bestScoreMove;
}