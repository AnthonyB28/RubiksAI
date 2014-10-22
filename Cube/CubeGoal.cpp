#include "Cube.h"
#include <queue>
#include <set>
#include <map>
#include <math.h>
#include <iostream>
#include <fstream>
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

	unsigned long long Cube::GetCornerHeuristicValue()
	{
		unsigned long long value = 1;
		static long sevenFact = 5040;
		static long eightFact = 40320;
		static unsigned long long biggestVal = 0;
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
			int threePow = (int) pow(3, i);
			//value += (position * 3 + CheckCornerValue(cornerCubies[i], i)) * GetFactorial(i - 1) * 3;
			value += (threePow * eightFact * CheckCornerValue(cornerCubies[i], i)) + (position * GetFactorial(i) * threePow); // (3^i * 8! * co_i) + (3^i * cp_i * i!)
			//value += (position * threePow + CheckCornerValue(cornerCubies[i], i)) * (eightFact / GetFactorial(i)) * threePow;
			cubesPos.erase(it);
		}
		DeleteCornerCubies(cornerCubies);
		if (value > biggestVal)
		{
			biggestVal = value;
		}
		return value;
	}

	void Cube::IASearch(int heuristic)
	{
		std::ofstream file;
		file.open("test.bin", std::ios::binary|std::ios::out|std::ios::trunc);
		std::queue<State*> q;
		q.push(new State(0, Cube::GetGoalCube())); // start with goal state

		std::map<unsigned long long, int> uniqueStates;
		unsigned long long skipped = 0;
		unsigned long long count = 0;
		// BFS
		while (!q.empty())
		{
			State* s = q.front();
			q.pop();
			int moveCount = s->m_MoveCount + 1;
			if (moveCount <= heuristic)
			{
				for (int moves = 0; moves < 18; ++moves)
				{
					State* newState = new State(moveCount, s->m_Cube);
					// All the possible moves generate their own state.
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
					case 12: newState->m_Cube.TurnTopCW(); newState->m_Cube.TurnTopCW(); break;
					case 13: newState->m_Cube.TurnBottomCW(); newState->m_Cube.TurnBottomCW(); break;
					case 14: newState->m_Cube.TurnLeftCW(); newState->m_Cube.TurnLeftCW(); break;
					case 15: newState->m_Cube.TurnRightCW(); newState->m_Cube.TurnRightCW(); break;
					case 16: newState->m_Cube.TurnFrontCW(); newState->m_Cube.TurnFrontCW(); break;
					case 17: newState->m_Cube.TurnBackCW(); newState->m_Cube.TurnBackCW(); break;
					}

					//s->m_Children.push_back(newState); Dont need this for now...
					unsigned long long hash = newState->m_Cube.GetCornerHeuristicValue();
					std::map<unsigned long long, int>::iterator setIt = uniqueStates.find(hash); 
					// If the hash doesnt exist, we need to add it to the queue else we delete and skip it.
					if (setIt == uniqueStates.end())
					{
						q.push(newState);
						file.seekp(hash);
						char moveNumToWrite = (char)moveCount; // Move counts shouldnt be more than 20, we can make these chars
						file.write(&moveNumToWrite,sizeof(char));
						uniqueStates[hash] = moveCount;
						//newState->m_Cube.LogCube();
					}
					else
					{
						if (uniqueStates[hash] != moveCount)
						{
							printf("\n Hash: %d RecordedMC: %d CurrentMC: %d", hash, uniqueStates[hash], moveCount);
						}
						skipped++;
						delete newState;
					}
					
					++count;
					if (count % 5000000 == 0)
					{
						printf("\nSkipped: %d - total: %d", skipped, count);
					}
				}
			}
			delete s;
		}
		printf("%d - total: %d", skipped, count);
		file.close();
	}

	Cube Cube::GetGoalCube()
	{
		Cube goal;
		for (int i = 0; i < 6; ++i)
		{
			for (int x = 0; x < 3; ++x)
			{
				for (int y = 0; y < 3; ++y)
				{
					goal.m_Faces[i].SetColor(x, y, i);
				}
			}
		}

		return goal;
	}
}