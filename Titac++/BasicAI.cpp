#include "BasicAI.h"
#include "GameMap.h"

#include <stdlib.h>


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
	m_minimaxCalls = 0;
	system("cls");
	Move move = minimax(0, m_gameMapPtr->getCurrentPlayerID(), -1, state_ptr);
	int x, y;
	m_gameMapPtr->getMap()->getPoint(move.moveIndex, x, y);
	return sf::Vector2i(x, y);
}

BasicAI::Move BasicAI::minimax(const int callParent, const unsigned int player, int parentMove, 
	GenericGrid<int> const * const state_ptr)
{
	std::vector<int> moves = getMovesFromState(state_ptr);
	std::vector<Move> scoreList;
	scoreList.reserve(moves.size());
	unsigned int playersCount = m_gameMapPtr->getPlayersCount();
	for (std::size_t i = 0; i < moves.size(); ++i)
	{
		++m_minimaxCalls;

		GenericGrid<int> changedState = *state_ptr;
		int x = 0;
		int y = 0;
		changedState.getPoint(moves[i], x, y);
		changedState[moves[i]] = player;
		sf::Vector2i newMove(x, y);

		std::cout << "call: " << m_minimaxCalls << ", parent: " << callParent 
			<< ", parent move id: " << parentMove << ", player: " << player << "\n";
		changedState.drawState();

		//check win
		if (m_gameMapPtr->checkWin(newMove, &changedState))
		{
			Move scoreMove;
			scoreMove.moveIndex = moves[i];
			scoreMove.callID = m_minimaxCalls;
			scoreMove.parentCall = callParent;
			if (player == m_myID)
			{
				scoreMove.score = 10;
				std::cout << "AI win\n";
			}
			else
			{
				scoreMove.score = -10;
				std::cout << "Human win\n";
			}
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
				Move scoreMove = minimax(m_minimaxCalls, nextPlayer, moves[i], &changedState);
				scoreList.push_back(scoreMove);
			}
			else
			{
				Move scoreMove;
				scoreMove.moveIndex = parentMove;
				scoreMove.parentCall = callParent;
				scoreMove.callID = m_minimaxCalls;
				scoreMove.score = 0;
				scoreList.push_back(scoreMove);
				std::cout << "Draw\n";
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

	std::cout << "Result for call: " << bestScoreMove.callID <<
		", parent: " << bestScoreMove.parentCall << ", parent move id: "
		<< bestScoreMove.moveIndex << ", player: " << player << "\n";
	return bestScoreMove;
}