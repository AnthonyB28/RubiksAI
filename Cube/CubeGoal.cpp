#include "Cube.h"
#include <queue>

namespace Rubiks
{
	struct Cube::State
	{
		State(std::vector<int>& previousMoves)
			: m_Explored(false)
			, m_MoveSet(previousMoves)
			, m_Children()
		{}

		bool m_Explored;
		std::vector<int> m_MoveSet;
		std::vector<State*> m_Children;
	};

	void Cube::GenerateBFS(State* state, int heuristic, std::vector<int>& previousMoves)
	{
		int moveCount = previousMoves.size();
		if (moveCount <= heuristic)
		{
			for (int moves = 0; moves < 12; ++moves)
			{
				State* newState = new State( previousMoves);
				newState->m_MoveSet.push_back(moves);
				state->m_Children.push_back(newState);
				GenerateBFS(newState, heuristic, newState->m_MoveSet);
			}
		}
	}

	// 				switch (moves)
	// 				{
	// 				case 0: newState->m_Cube.TurnTopCW(); break;
	// 				case 1: newState->m_Cube.TurnTopACW(); break;
	// 				case 2: newState->m_Cube.TurnBottomCW(); break;
	// 				case 3: newState->m_Cube.TurnBottomACW(); break;
	// 				case 4: newState->m_Cube.TurnLeftCW(); break;
	// 				case 5: newState->m_Cube.TurnLeftACW(); break;
	// 				case 6: newState->m_Cube.TurnRightCW(); break;
	// 				case 7: newState->m_Cube.TurnRightACW(); break;
	// 				case 8: newState->m_Cube.TurnFrontCW(); break;
	// 				case 9: newState->m_Cube.TurnFrontACW(); break;
	// 				case 10: newState->m_Cube.TurnBackCW(); break;
	// 				case 11: newState->m_Cube.TurnBackACW(); break;
	// 				}


	void Cube::IASearch(int heuristic)
	{
		std::queue<State*> q;
		State* goalState = new State(std::vector<int>());
		//GenerateBFS(goalState, heuristic, std::vector<int>());
		goalState->m_Explored = false;
		q.push(goalState);

		while (!q.empty())
		{
			State* s = q.front();
			q.pop();

			if (s->m_MoveSet.size() <= heuristic)
			{
				for (int moves = 0; moves < 12; ++moves)
				{
					State* newState = new State(s->m_MoveSet);
					newState->m_MoveSet.push_back(moves);
					s->m_Children.push_back(newState);
					q.push(newState);
				}
			}
			delete s;
		}
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