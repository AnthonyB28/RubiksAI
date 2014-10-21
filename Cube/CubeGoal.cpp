#include "Cube.h"
#include <queue>
#include <set>

namespace Rubiks
{
	struct Cube::State
	{
		State(int moveCount, Cube& cube)
			: m_MoveCount(moveCount)
			, m_Cube(cube)
			, m_Children()
		{}

		//bool m_Explored;
		int m_MoveCount;
		Cube m_Cube;
		std::vector<State*> m_Children;
	};

	int GetFactorial(int i)
	{
		int factorial = 1;
		for (int fact = 1; fact <= i; ++fact)
		{
			factorial *= fact;
		}
		return factorial;
	}

	long Cube::GetCornerHeuristicValue()
	{
		long value = 1;
		//c1 * 3 + o1) * 0! * 3 + (c2 * 3 + o2) * 1! * 3 + (c3 * 3 + o3) * 2! * 3
		// o = CheckCornerValue c = GetCornerPermutationValue
		UInt32** cornerCubies = this->GetCornerCubies();
		std::vector<int> cubesPos;
		for (int x = 0; x < 8; ++x)
		{
			cubesPos.push_back(GetCornerPermutationValue(cornerCubies[x]));
		}
		for (int i = 0; i < 7; ++i)
		{
			std::vector<int>::iterator it = find(cubesPos.begin(), cubesPos.end(), i);
			int position = it - cubesPos.begin();
			value += (position * 3 + (CheckCornerValue(cornerCubies[i], i)+1)) * (i+1) * 3;
			cubesPos.erase(it);
		}
		DeleteCornerCubies(cornerCubies);
		return value;
	}

// 	void Cube::GenerateDFS(State* state, int heuristic, std::vector<int>& previousMoves)
// 	{
// 		int moveCount = previousMoves.size();
// 		if (moveCount <= heuristic)
// 		{
// 			for (int moves = 0; moves < 12; ++moves)
// 			{
// 				State* newState = new State( previousMoves);
// 				newState->m_MoveSet.push_back(moves);
// 				state->m_Children.push_back(newState);
// 				GenerateDFS(newState, heuristic, newState->m_MoveSet);
// 			}
// 		}
// 	}




	void Cube::IASearch(int heuristic)
	{
		std::queue<State*> q;
		State* goalState = new State(0, *Cube::GetGoalCube());
		//GenerateBFS(goalState, heuristic, std::vector<int>());
		//goalState->m_Explored = false;
		q.push(goalState);

		std::set<long> uniqueStates;
		int skipped = 0;
		while (!q.empty())
		{
			State* s = q.front();
			q.pop();
			int moveCount = s->m_MoveCount + 1;
			if (moveCount <= heuristic)
			{
				for (int moves = 0; moves < 12; ++moves)
				{
					State* newState = new State(moveCount, s->m_Cube);
					switch (moves)
					{
					case 0: newState->m_Cube.TurnTopCW(); break;
					case 1: newState->m_Cube.TurnTopACW(); break;
					case 2: newState->m_Cube.TurnBottomCW(); break;
					case 3: newState->m_Cube.TurnBottomACW(); break;
					case 4: newState->m_Cube.TurnLeftCW(); break;
					case 5: newState->m_Cube.TurnLeftACW(); break;
					case 6: newState->m_Cube.TurnRightCW(); break;
					case 7: newState->m_Cube.TurnRightACW(); break;
					case 8: newState->m_Cube.TurnFrontCW(); break;
					case 9: newState->m_Cube.TurnFrontACW(); break;
					case 10: newState->m_Cube.TurnBackCW(); break;
					case 11: newState->m_Cube.TurnBackACW(); break;
					}

					s->m_Children.push_back(newState);
					long hash = newState->m_Cube.GetCornerHeuristicValue();
					std::set<long>::iterator setIt = uniqueStates.find(hash);
					if (setIt == uniqueStates.end())
					{
						q.push(newState);
						uniqueStates.insert(hash);
					}
					else
					{
						skipped++;
					}
				}
			}
			delete s;
		}
		printf("%d", skipped);
	}

	Cube* Cube::GetGoalCube()
	{
		Cube* goal = new Cube();
		for (int i = 0; i < 6; ++i)
		{
			for (int x = 0; x < 3; ++x)
			{
				for (int y = 0; y < 3; ++y)
				{
					goal->m_Faces[i].SetColor(x, y, i);
				}
			}
		}

		return goal;
	}
}