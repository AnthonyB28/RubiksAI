#include "Cube.h"
#include <queue>
#include <math.h>
#include <iostream>
#include <fstream>
namespace Rubiks
{
	struct Cube::State
	{
		// Each Cube state is only ~22 bytes!
		State(int moveCount, Cube& cube)
			: m_PreviousMove(0)
			, m_MoveCount(moveCount)
			, m_Cube(cube)
		{}

		unsigned int m_PreviousMove : 5; // 0 - 32
		unsigned int m_MoveCount : 5; // Total # of moves to this position
		Cube m_Cube;
		//std::vector<State*> m_Children; // We dont need children for this assignment technically.
	};

	// No greater than 8
	inline int GetFactorial(int num)
	{
		if (num <= 1) { return 1; }
		else if (num == 2) { return 2; }
		else if (num == 3) { return 6; }
		else if (num == 4) { return 24; }
		else if (num == 5) { return 120; }
		else if (num == 6) { return 720; }
		else if (num == 7) { return 5040; }
		else if (num == 8) { return 40320; }
		else
		{
			return 1;
		}
	}

	unsigned long long Cube::GetCornerHeuristicValue()
	{
		unsigned long long value = 1;
		static long eightFact = 40320;
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
			int threePow = (int)pow(3, i);
			int orientation = CheckCornerValue(cornerCubies[i], i);
			value += (position * 3 + CheckCornerValue(cornerCubies[i], i)) * (eightFact / GetFactorial(8 - i)) * threePow; //(cp_i * 3^i + co_i) * (8! / 8-i!) * 3^i
			//value += (position * 3 + CheckCornerValue(cornerCubies[i], i)) * GetFactorial(i - 1) * 3;
			//value += (threePow * eightFact * orientation) + (position * GetFactorial(i) * threePow); // (3^i * 8! * co_i) + (3^i * cp_i * i!)
			cubesPos.erase(it);
		}
		DeleteCornerCubies(cornerCubies);
		return value;
	}

	void Cube::GenerateTables(int heuristic)
	{
		std::vector<int> *uniqueStates = new std::vector < int > ;
		uniqueStates->resize(88179841, -1);
		std::queue<State*> q;
		q.push(new State(0, Cube::GetGoalCube())); // start with goal state
		unsigned long long skipped = 0;
		unsigned long long count = 0;
		// BFS
		while (!q.empty())
		{
			State* curState = q.front();
			q.pop();
			int moveCount = curState->m_MoveCount + 1;
			if (moveCount <= heuristic)
			{
				// Generate a state for every possible move (18 of them)
				for (int currentMove = 0; currentMove < 18; ++currentMove)
				{
					// Only make a new state if the previous move is not repeated in anyway.
					if (currentMove != curState->m_PreviousMove && currentMove != (curState->m_PreviousMove + 1) && currentMove != (curState->m_PreviousMove + 2))
					{
						State* newState = new State(moveCount, curState->m_Cube);
						newState->m_PreviousMove = currentMove;
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

						
						//s->m_Children.push_back(newState); Dont need this?....
						unsigned long long hash = newState->m_Cube.GetCornerHeuristicValue();
						// If the hash doesnt exist, we need to add it to the queue else we delete and skip it.
						if (uniqueStates->at(hash) == -1)
						{
							q.push(newState);
							uniqueStates->at(hash) = moveCount;
						}
						else // Hash existed, we can safely skip. Unless stored hash is bigger? Should be impossible. Log it
						{
// 							if (uniqueStates->at(hash) > moveCount)
// 							{
// 								std::cout.imbue(std::locale(""));
// 								std::cout << "\nHash: " << hash << " RecordedMC: " << uniqueStates->at(hash) << " CurrentMC: " << moveCount;
// 							}
							skipped++;
							delete newState;
						}

						++count;
						if (count % 10000000 == 0)
						{
							std::cout.imbue(std::locale(""));
							std::cout << "\nSkipped: " << skipped << " - total: " << count;
						}
					}
				}
			}
			delete curState;
		}
		printf("\n Skipped: %d - total: %d - Unique: %d", skipped, count, count-skipped);
		std::fstream file;
		file.open("test.bin", std::ios::binary | std::ios::out | std::ios::trunc | std::ios::in);
		unsigned long long missed = 0;
		for (int hash = 0; hash < 88179841; ++hash)
		{
			if (uniqueStates->at(hash) != -1)
			{
				unsigned long long byteLoc = hash;
				bool secondNum = false;
				if (byteLoc % 2 != 0)
				{
					// Odd, must be combined
					byteLoc -= 1;
					secondNum = true;
				}
				byteLoc /= 2; // If we have byteLoc 5, 5-1 = 4, then 4/2 = 2. Write at byte 2.
				file.seekg(byteLoc);
				char moveByte;
				file.read(&moveByte, sizeof(char));
				if (secondNum) // We already have the first number stored. So insert second number.
				{
					moveByte |= (char)(uniqueStates->at(hash) & 0x0F);
				}
				else
				{
					moveByte = (char)(uniqueStates->at(hash) << 4); // Store our first number as normal.
				}
				file.clear(); // This is necessary to write after reading.
				file.seekp(byteLoc);
				file.write(&moveByte, sizeof(char));
			}
			else
			{
				++missed;
			}
		}
		printf("\nSkipped array %d", missed);
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