#include "Cube.h"
#include <stack>
#include <algorithm>
#include <iostream>
#include <boost/timer.hpp>

namespace Rubiks
{

	// Returns the min or max of the 3 possible move counts from corners, edgesA, edgesB from their hash table
	int Cube::GetMaxMinMoveSolve(bool max, std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB) const
	{
		unsigned long long cornerHash = GetCornerHash();
		unsigned long long edgeHashA = GetEdgeHash(true);
		unsigned long long edgeHashB = GetEdgeHash(false);
		int moveCountCorner;
		int moveCountEdgeA;
		int moveCountEdgeB;
		unsigned char byteNum;
		if (cornerHash % 2 != 0)
		{
			byteNum = (unsigned char)cornerMap.at((cornerHash - 1) / 2);
			moveCountCorner = byteNum & 0x0F;
		}
		else
		{
			byteNum = (unsigned char)cornerMap.at(cornerHash / 2);
			moveCountCorner = byteNum >> 4;
		}
		if (edgeHashA % 2 != 0)
		{
			byteNum = (unsigned char)edgeMapA.at((edgeHashA - 1) / 2);
			moveCountEdgeA = byteNum & 0x0F;
		}
		else
		{
			byteNum = (unsigned char)edgeMapA.at(edgeHashA / 2);
			moveCountEdgeA = byteNum >> 4;
		}
		if (edgeHashB % 2 != 0)
		{
			byteNum = (unsigned char)edgeMapB.at((edgeHashB - 1) / 2);
			moveCountEdgeB = byteNum & 0x0F;
		}
		else
		{
			byteNum = (unsigned char)edgeMapB.at(edgeHashB / 2);
			moveCountEdgeB = byteNum >> 4;
		}

		if (max)
		{
			int maxCountCA = (moveCountCorner > moveCountEdgeA ? moveCountCorner : moveCountEdgeA);
			return maxCountCA > moveCountEdgeB ? maxCountCA : moveCountEdgeB;
		}
		else
		{
			int minCountCA = (moveCountCorner < moveCountEdgeA ? moveCountCorner : moveCountEdgeA);
			return minCountCA < moveCountEdgeB ? minCountCA : moveCountEdgeB;
		}
	}

	// A cube state specifically for IDA* search
	struct Cube::IDAState
	{
		// Each Cube state is only ~22 bytes!
		IDAState(std::vector<int> const & prevMoves, Cube const & cube)
			: m_Cube(cube)
			, m_PrevMoves(prevMoves) // 30 is a placeholder so we don't skip the goal state at 0
			, m_CutOff(false)
		{}

		Cube m_Cube;
		std::vector<int> m_PrevMoves; // All the previous moves made up to this state, our g(n) for depth
		bool m_CutOff = false;
	};

	Cube::IDAState Cube::IterativeDepthSearch(IDAState & state, unsigned int const limit, std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB)
	{
		// Don't exceed f(n) = g(n) + h(n)
		static boost::timer t;
		static unsigned long long nodes = 0;
		static unsigned long long skippedNodes = 0;
		IDAState * copyState = new IDAState(state.m_PrevMoves, state.m_Cube);
		std::stack<IDAState *> s;
		s.push(copyState);
		while (!s.empty())
		{
			IDAState * currentState = s.top();
			s.pop();
			int h = currentState->m_Cube.GetMaxMinMoveSolve(true, cornerMap, edgeMapA, edgeMapB); // h(n) 
			if (h == 0) // We've solved the cube.
			{
				std::cout << "\nNodes: " << nodes;
				return *currentState;
			}
			else if (currentState->m_PrevMoves.size() + h > limit) // If prevMove + h > limit for f(n) = g(n) + h(n), we need to cut off
			{
				delete currentState;
			}
			else
			{
				int lastMove;
				if (state.m_PrevMoves.size() > 0) // Make sure we're not doing the initial state, else we go out of bounds.
				{
					lastMove = currentState->m_PrevMoves[currentState->m_PrevMoves.size() - 1];
				}
				else
				{
					lastMove = 30; // Placeholder for first move TODO fix this
				}

				// Generate a state for every possible move (18 of them)
				for (int currentMove = 0; currentMove < 18; ++currentMove)
				{
					++nodes;
					if (nodes % 1000000 == 0)
					{
						std::cout << "\nNodes: " << nodes << " - " << t.elapsed();
						t.restart();
					}
					// Only make a new state if the previous move is not repeated in anyway.
					if (currentMove != lastMove &&
						currentMove != (lastMove + 1) &&
						currentMove != (lastMove + 2))
					{
						Cube::IDAState * newState = new Cube::IDAState(currentState->m_PrevMoves, currentState->m_Cube);
						newState->m_PrevMoves.push_back(currentMove);
						switch (currentMove) // Manipulate the state with a move action
						{
						case 0: newState->m_Cube.TurnTopCW(); break;
						case 1: newState->m_Cube.TurnTopACW(); break;
						case 2: newState->m_Cube.TurnTopCW(); newState->m_Cube.TurnTopCW(); break;
						case 3: newState->m_Cube.TurnBottomCW(); break;
						case 4: newState->m_Cube.TurnBottomACW(); break;
						case 5: newState->m_Cube.TurnBottomCW(); newState->m_Cube.TurnBottomCW(); break;
						case 6: newState->m_Cube.TurnLeftCW(); break;
						case 7: newState->m_Cube.TurnLeftACW(); break;
						case 8: newState->m_Cube.TurnLeftCW(); newState->m_Cube.TurnLeftCW(); break;
						case 9: newState->m_Cube.TurnRightCW(); break;
						case 10: newState->m_Cube.TurnRightACW(); break;
						case 11: newState->m_Cube.TurnRightCW(); newState->m_Cube.TurnRightCW(); break;
						case 12: newState->m_Cube.TurnFrontCW(); break;
						case 13: newState->m_Cube.TurnFrontACW(); break;
						case 14: newState->m_Cube.TurnFrontCW(); newState->m_Cube.TurnFrontCW(); break;
						case 15: newState->m_Cube.TurnBackCW(); break;
						case 16: newState->m_Cube.TurnBackACW(); break;
						case 17: newState->m_Cube.TurnBackCW(); newState->m_Cube.TurnBackCW(); break;
						}
						s.push(newState);
					}
				}
				delete currentState;
			}
		}

		state.m_CutOff = true; // Didn't find anything in our stack... No solution
		return state;
	}

	Cube::IDAState Cube::IDASearch(IDAState & state, std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB)
	{
		//int maxCount = state.m_Cube.GetMaxMinMoveSolve(cornerMap, edgeMapA, edgeMapB);
		for (int i = 0; i <= 20; ++i)
		{
			Cube::IDAState result = IterativeDepthSearch(state, i, cornerMap, edgeMapA, edgeMapB);
			if (!result.m_CutOff)
			{
				printf("\nsolution @ %d", i);
				return result;
			}
		}
		printf("\nDidnt find solution");
		state.m_CutOff = true;
		return state;
	}

	void Cube::Solve(std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB) const
	{
		boost::timer t;
		// f = g + h where g = cost to get to this node and h = heuristic estimate of getting to goal
		// search node as long as f <= threshold, or f >= threshold in our case?
		IDAState result = IDASearch(IDAState(std::vector<int>(), *this), cornerMap, edgeMapA, edgeMapB);
		printf("\nTime to solve: %f ", t.elapsed());
		if (result.m_CutOff)
		{
			return;
		}
		std::string solveTurns;
		for (std::vector<int>::iterator it = result.m_PrevMoves.begin(); it != result.m_PrevMoves.end(); ++it)
		{
			switch (*it)
			{
			case 0: solveTurns.append("Y1"); break;
			case 1: solveTurns.append("Y3"); break;
			case 2: solveTurns.append("Y2"); break;
			case 3: solveTurns.append("W1"); break;
			case 4: solveTurns.append("W3"); break;
			case 5: solveTurns.append("W2"); break;
			case 6: solveTurns.append("G1"); break;
			case 7: solveTurns.append("G3"); break;
			case 8: solveTurns.append("G2"); break;
			case 9: solveTurns.append("B1"); break;
			case 10: solveTurns.append("B3"); break;
			case 11: solveTurns.append("B2"); break;
			case 12: solveTurns.append("O1"); break;
			case 13: solveTurns.append("O3"); break;
			case 14: solveTurns.append("O2"); break;
			case 15: solveTurns.append("R1"); break;
			case 16: solveTurns.append("R3"); break;
			case 17: solveTurns.append("R2"); break;
			}
		}

		printf("\n SOLUTION: %s", solveTurns.c_str());
	}
}