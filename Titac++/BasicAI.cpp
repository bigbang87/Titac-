#include "BasicAI.h"
#include "GameMap.h"

#include <stdlib.h>


BasicAI::BasicAI(const unsigned int myID, GameMap const * const gameMapPtr) : m_gameMapPtr(gameMapPtr), m_myID(myID)
{
	std::cout << "BasicAI player initialized \n";
	m_steps = 0;
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
	m_steps = 0;
	system("cls");
	/*std::cout << "Initial state (step 0):\n";
	state_ptr->drawState();
	std::cout << "\n";*/
	Move move = minimax(0, m_gameMapPtr->getCurrentPlayerID(), -1, state_ptr);
	int x, y;
	m_gameMapPtr->getMap()->getPoint(move.moveIndex, x, y);
	return sf::Vector2i(x, y);
}

BasicAI::Move BasicAI::minimax(const int parentStep, const unsigned int player, int parentMove, 
	GenericGrid<int> const * const state_ptr)
{
	const bool debugMode = false;
	std::vector<int> moves = getMovesFromState(state_ptr);
	std::vector<Move> scoreList;
	scoreList.reserve(moves.size());
	unsigned int playersCount = m_gameMapPtr->getPlayersCount();
	for (std::size_t i = 0; i < moves.size(); ++i)
	{
		++m_steps;

		GenericGrid<int> changedState = *state_ptr;
		int x = 0;
		int y = 0;
		changedState.getPoint(moves[i], x, y);
		changedState[moves[i]] = player;
		sf::Vector2i newMove(x, y);

		if (debugMode)
		{
			std::cout << "step: " << m_steps << ", parentStep: " << parentStep
				<< ", parent move: " << parentMove << ", player: " << state_ptr->getLiteralFigure(player) << "\n";
			changedState.drawState();
		}

		//check win
		if (m_gameMapPtr->checkWin(newMove, &changedState))
		{
			Move scoreMove;
			scoreMove.moveIndex = moves[i];
			scoreMove.thisStep = m_steps;
			scoreMove.parentStep = parentStep;
			if (player == m_myID)
			{
				scoreMove.score = 10;
				if (debugMode)
					std::cout << "Win\n";
			}
			else
			{
				scoreMove.score = -10;
				if (debugMode)
					std::cout << "Loose\n";
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
				Move scoreMove = minimax(m_steps, nextPlayer, moves[i], &changedState);
				scoreList.push_back(scoreMove);
			}
			else
			{
				Move scoreMove;
				if (parentMove == -1)
					scoreMove.moveIndex = moves[i];
				else
					scoreMove.moveIndex = parentMove;
				scoreMove.parentStep = parentStep;
				scoreMove.thisStep = m_steps;
				scoreMove.score = 0;
				scoreList.push_back(scoreMove);
				if (debugMode)
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
	//dodane
	if (parentMove != -1)
		bestScoreMove.moveIndex = parentMove;
	//end dodane
	if (debugMode)
	{
		std::cout << "Result for step: " << bestScoreMove.thisStep <<
			", parentSept: " << bestScoreMove.parentStep << ", parent move: "
			<< bestScoreMove.moveIndex << ", player: " << state_ptr->getLiteralFigure(player) << "\n";
	}
	return bestScoreMove;
}