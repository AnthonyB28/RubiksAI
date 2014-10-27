#define _CRT_SECURE_NO_DEPRECATE
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
			: m_PreviousMove(30)
			, m_MoveCount(moveCount)
			, m_Cube(cube)
		{}

		unsigned int m_PreviousMove : 5; // 0 - 32
		unsigned int m_MoveCount : 4; // Total # of moves to this position
		Cube m_Cube;
		//std::vector<State*> m_Children; // We dont need children for this assignment technically.
	};

	// 12 static
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
		else if (num == 9) { return 362880; }
		else if (num == 10) { return 3628800; }
		else if (num == 11) { return 39916800; }
		else if (num == 12) { return 479001600; }
		else
		{
			return num* GetFactorial(num - 1);
		}
	}

	unsigned long long Cube::GetCornerHeuristicValue()
	{
		unsigned long long value = 1;
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
			int orientation = GetCornerOrientationValue(cornerCubies[i], i);
			value += (position * 3 + orientation) * (GetFactorial(8) / GetFactorial(8 - i)) * threePow; //(cp_i * 3 + co_i) * (8! / 8-i!) * 3^i
			cubesPos.erase(it);
		}
		static unsigned long long largestValue = 0;
		if (value > largestValue)
		{
			largestValue = value;
			printf("\n%d", largestValue);
		}
		DeleteCornerCubies(cornerCubies);
		return value;
	}

	// True if from 1 to 6, else from 7 to 12
	unsigned long long Cube::GetEdgeHueristicValue(bool setA)
	{
		unsigned long long value = 1;
		UInt32** edgeCubies = this->GetEdgeCubies();
		std::vector<int> cubesPos;
		for (int x = 0; x < 12; ++x) //Just for one set of cubes, we need to do 6 to 12 next
		{
			int value = GetEdgePermutationValue(edgeCubies[x]);
			if (setA && value >= 0 && value < 6)
			{
				cubesPos.push_back(value);
			}
			else if(!setA && value >= 6 && value < 12)
			{
				cubesPos.push_back(value);
			}
		}
		int i = 5;
		int maxI = 0;
		if (!setA)
		{
			i = 6;
			maxI = 12;
		}
		for (; i >= maxI; --i)
		{
			std::vector<int>::iterator it = find(cubesPos.begin(), cubesPos.end(), i);
			int position = it - cubesPos.begin();
			int twoPow = (int)pow(2, i);
			int orientation = GetEdgeOrientationValue(edgeCubies[i], i);
			value += (position * 2 + orientation) * (GetFactorial(12) / GetFactorial(12 - i)) * twoPow; //(cp_i * 2 + co_i) * (11-i! / 6!) * 2^i
			//value += ((GetFactorial(i) * position) + (2 * orientation * GetFactorial(11))) / GetFactorial(6);
			//value += (position * 3 + CheckCornerValue(cornerCubies[i], i)) * GetFactorial(i - 1) * 3;
			//value += (threePow * eightFact * orientation) + (position * GetFactorial(i) * threePow); // (3^i * 8! * co_i) + (3^i * cp_i * i!)
			cubesPos.erase(it);
		}
		DeleteEdgeCubies(edgeCubies);
		static unsigned long long largestValue = 0;
		if (value > largestValue)
		{
			largestValue = value;
			printf("\n%d", largestValue);
		}
		return value;
	}

	void Cube::ReadCornersFile()
	{
		std::fstream file;
		file.open("corners1.bin", std::ios::binary | std::ios::in);
		unsigned long long maxHash = 88179841 / 2;
			int zeroCount = 0;
			int twoCount = 0;
			int threeCount = 0;
			int fourCount = 0;
			int fiveCount = 0;
		for (int hash = 0; hash < maxHash; ++hash)
		{
			unsigned long long hash1 = hash * 2;
			unsigned long long hash2 = hash * 2 + 1;
			file.seekg(hash);
			char byteNum;
			file.read(&byteNum, sizeof(unsigned char));
			unsigned char testing = (unsigned char) byteNum;
			 int moveCount1 = testing >> 4;
			 int moveCount2 = byteNum & 0x0F;
			printf("\nHash 1: %d = %d | Hash 2: %d = %d", hash1, moveCount1, hash2, moveCount2);
			file.clear();
			if (moveCount1 == 0 || moveCount2 == 0)
			{
				++zeroCount;
			}
			if (moveCount1 == 2 || moveCount2 == 2)
			{
				++twoCount;
			}
			if (moveCount1 == 3 || moveCount2 == 3)
			{
				++threeCount;
			}
			if (moveCount1 == 4 || moveCount2 == 4)
			{
				++fourCount;
			}
		}
		file.close();
		printf("\n%d - %d - %d - %d", zeroCount, twoCount, threeCount, fourCount);
	}

	void Cube::GenerateCornerTables(int heuristic)
	{
		std::vector<int> *uniqueStates = new std::vector < int > ;
		uniqueStates->resize(88179841, -1);
		std::queue<State*> q;
		q.push(new State(0, Cube::GetGoalCube())); // start with goal state
		uniqueStates->at(q.front()->m_Cube.GetCornerHeuristicValue()) = 0; // Make sure we save the goal state's value
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
						if (uniqueStates->at(hash) == -1 || uniqueStates->at(hash) > moveCount)
						{
							q.push(newState);
							uniqueStates->at(hash) = moveCount;
						}
						else // Hash existed, we can safely skip. Unless stored hash is bigger? Should be impossible. Log it
						{
							if (uniqueStates->at(hash) > moveCount)
							{
								std::cout.imbue(std::locale(""));
								std::cout << "\nHash: " << hash << " RecordedMC: " << uniqueStates->at(hash) << " CurrentMC: " << moveCount;
								return;
							}
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
		printf("\n Skipped: %d - total: %d - Unique: %d", skipped, count, count - skipped);
		std::fstream file;
		file.open("corners1.bin", std::ios::binary | std::ios::out | std::ios::trunc);
		unsigned long long missed = 0;
		for (int hash = 0; hash < 88179841; hash += 2)
		{
			// Always do even.
			if (uniqueStates->at(hash) != -1)
			{
				unsigned long long byteLoc = hash;
				byteLoc /= 2; // Always an even number.
				char moveByte;
				moveByte = uniqueStates->at(hash) << 4; // Store our first number as normal.
				if (hash + 1 < 88179841) // prevent overflow
				{
					moveByte |= uniqueStates->at(hash + 1) & 0x0F;
				}
				file.clear(); // This is necessary to write after reading.
				file.seekp(byteLoc);
				file.write(&moveByte, sizeof(char));
			}
			else
			{
				printf("\n%d HashSkipped", hash);
				++missed;
			}
		}
		printf("\nSkipped array %d", missed);
		file.close();
	}

	void Cube::GenerateEdgeTables(int heuristic)
	{
		std::vector<int> *uniqueStates = new std::vector < int > ;
		uniqueStates->resize(42577921, -1);
		std::queue<State*> q;
		q.push(new State(0, Cube::GetGoalCube())); // start with goal state
		uniqueStates->at(q.front()->m_Cube.GetEdgeHueristicValue(true)) = 0; // Make sure we save the goal state's value
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
						//unsigned long long hash = newState->m_Cube.GetCornerHeuristicValue();
						unsigned long long hash = newState->m_Cube.GetEdgeHueristicValue(true);
						// If the hash doesnt exist, we need to add it to the queue else we delete and skip it.
						if (uniqueStates->at(hash) == -1)
						{
							q.push(newState);
							uniqueStates->at(hash) = moveCount;
						}
						else // Hash existed, we can safely skip. Unless stored hash is bigger? Should be impossible. Log it
						{
							if (uniqueStates->at(hash) > moveCount)
							{
								std::cout.imbue(std::locale(""));
								std::cout << "\nHash: " << hash << " RecordedMC: " << uniqueStates->at(hash) << " CurrentMC: " << moveCount;
								return;
							}
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
		file.open("Edges.bin", std::ios::binary | std::ios::out | std::ios::trunc);
		unsigned long long missed = 0;
		for (int hash = 0; hash < 42577921; hash += 2)
		{
			// Always do even.
			if (uniqueStates->at(hash) != -1)
			{
				unsigned long long byteLoc = hash;
				byteLoc /= 2; // Always an even number.
				char moveByte;
				unsigned int moveCount1 = uniqueStates->at(hash);
				moveByte = moveCount1 << 4; // Store our first number as normal.
				if (hash + 1 < 42577921) // prevent overflow
				{
					unsigned int moveCount2 = uniqueStates->at(hash + 1);
					moveByte |= moveCount2 & 0x0F;
				}
				file.clear(); // This is necessary to write after reading.
				file.seekp(byteLoc);
				file.write(&moveByte, sizeof(char));
			}
			else
			{
				printf("\n%d HashSkipped", hash);
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