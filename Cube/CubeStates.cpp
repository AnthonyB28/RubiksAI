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
			: m_PreviousMove(30) // 30 is a placeholder so we don't skip the goal state at 0
			, m_MoveCount(moveCount)
			, m_Cube(cube)
		{}

		unsigned int m_PreviousMove : 5; // 0 - 32
		unsigned int m_MoveCount : 4; // Total # of moves to this position
		Cube m_Cube;
		//std::vector<State*> m_Children; // We dont need children for this assignment technically.
	};

	// Returns a representation of a goal state Rubiks Cube.
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

	// Up to 12 is precomputed
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

	void Cube::ReadTableFile(char* fileName, bool corners)
	{
		std::fstream file;
		file.open(fileName, std::ios::binary | std::ios::in);
		unsigned long long maxHash = 0;
		if (corners)
		{
			maxHash = 88179841 / 2;
		}
		else
		{
			maxHash = 42577921 / 2;
		}
		std::vector<unsigned int> numCounts{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
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
			//printf("\nHash 1: %d = %d | Hash 2: %d = %d", hash1, moveCount1, hash2, moveCount2);
			file.clear();
			if (moveCount1 >= 0)
			{
				++numCounts.at(moveCount1);
			}
			if (moveCount2 >= 0)
			{
				++numCounts.at(moveCount2);
			}
		}
		file.close();
		for (int i = 0; i < 12; ++i)
		{
			std::cout << numCounts.at(i) << " - ";
		}
	}

	// Generates a hash table for all the unique states of corners for a given hueristic, and writes it to a file. 
	// Heuristic shouldnt be larger than 12
	void Cube::GenerateCornerTables(int heuristic)
	{
		if (heuristic > 12)
		{
			printf("\n Too large of heuristic to generate Corner Tables.");
			return;
		}

		std::vector<int> *uniqueStates = new std::vector < int > ;
		uniqueStates->resize(88179841, -1);
		std::queue<State*> q;
		q.push(new State(0, Cube::GetGoalCube())); // start with goal state
		uniqueStates->at(q.front()->m_Cube.GetCornerHash()) = 0; // Make sure we save the goal state's value
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
					if (currentMove != curState->m_PreviousMove && 
						currentMove != (curState->m_PreviousMove + 1) && 
						currentMove != (curState->m_PreviousMove + 2))
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
						unsigned long long hash = newState->m_Cube.GetCornerHash();
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

	// Returns the hash for corners for a Cube's state
	unsigned long long Cube::GetCornerHash()
	{
		unsigned long long value = 1;
		UInt32** cornerCubies = this->GetCornerCubies();
		std::vector<int> cubesPos; // From corners 0 to 7, stores the value of cubies
		std::vector<int> absCubesPos; // ABSOLUTE corner positions, immutable don't change
		for (int x = 0; x < 8; ++x)
		{
			int cornerValue = GetCornerPermutationValue(cornerCubies[x]);
			cubesPos.push_back(cornerValue);
			absCubesPos.push_back(cornerValue);
		}
		for (int i = 0; i < 7; ++i) // For each corner cubie VALUE (eg RYG = 0)
		{
			std::vector<int>::iterator posIt = find(cubesPos.begin(), cubesPos.end(), i); // Find where the corner cubie is dynamically
			std::vector<int>::iterator absPosIt = find(absCubesPos.begin(), absCubesPos.end(), i); // Find where the corner cubie is absolutely
			int positionVal = posIt - cubesPos.begin(); // Where is this cubie in the modified collection!
			int absPosition = absPosIt - absCubesPos.begin(); // Where is this cubie in our cornerCubies collection!
			int threePow = (int)pow(3, i);
			int orientation = GetCornerOrientationValue(cornerCubies[absPosition], absPosition); // Check the cubie orientation in its actual position.
			value += (positionVal * 3 + orientation) * (GetFactorial(8) / GetFactorial(8 - i)) * threePow; //(cp_i * 3 + co_i) * (8! / 8-i!) * 3^i
			cubesPos.erase(posIt);
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


	// Generates a hash table for all the unique states of one set of edges for a given hueristic, and writes it to a file.
	// Heuristic shouldnt be larger than 11
	void Cube::GenerateEdgeTables(int heuristic)
	{
		if (heuristic > 11)
		{
			printf("\nHeuristic too large for edge tables");
			return;
		}

		std::vector<int> *uniqueStates = new std::vector < int > ;
		uniqueStates->resize(42577921, -1);
		std::queue<State*> q;
		q.push(new State(0, Cube::GetGoalCube())); // start with goal state
		uniqueStates->at(q.front()->m_Cube.GetEdgeHash(true)) = 0; // Make sure we save the goal state's value
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
					if (currentMove != curState->m_PreviousMove && 
						currentMove != (curState->m_PreviousMove + 1) && 
						currentMove != (curState->m_PreviousMove + 2))
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

						unsigned long long hash = newState->m_Cube.GetEdgeHash(true);
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
						if (count % 10000 == 0)
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

	// True if from 1 to 6, else from 7 to 12
	unsigned long long Cube::GetEdgeHash(bool setA)
	{
		unsigned long long value = 1;
		UInt32** edgeCubies = this->GetEdgeCubies();
		std::vector<int> cubesPos;
		std::vector<int> absCubesPos;
		for (int x = 0; x < 12; ++x) //Just for one set of cubes, we need to do 6 to 12 next
		{
			int value = GetEdgePermutationValue(edgeCubies[x]); // What cubie is in position x
			cubesPos.push_back(value);
			absCubesPos.push_back(value);
		}
		int i = 0;
		int maxI = 6;
		int count = 0; // Independent from i because of dual edge sets.
		if (!setA)
		{
			i = 6;
			maxI = 12;
		}
		for (; i < maxI; ++i) // i is the Cubie edge value (e.g i = RW cubie)
		{
			std::vector<int>::iterator posIt = find(cubesPos.begin(), cubesPos.end(), i); // Find where the corner cubie is dynamically
			std::vector<int>::iterator absPosIt = find(absCubesPos.begin(), absCubesPos.end(), i); // Find where the corner cubie is absolutely
			int position = posIt - cubesPos.begin(); // Where is this cubie in the modified collection!
			int absPosition = absPosIt - absCubesPos.begin(); // Where is this cubie in our cornerCubies collection!
			cubesPos.erase(posIt);
			int orientation = GetEdgeOrientationValue(edgeCubies[absPosition], absPosition); // We want the orientation of cubie i at its position
			int twoPow = (int)pow(2, 5-count);
			// (p * 2 + o) * (12-count!/ 6!) * 2
			value += (position * 2 + orientation) * ((GetFactorial(11 - count) / GetFactorial(6)) * twoPow);

			// (p * 2^i + o * 12) * (12! / 12-i!) * 2^i
			// With * 12 it gets to 42.1 mil~ and without its 39 mil~
			//value += (position * 2 * orientation) * (GetFactorial(11) / GetFactorial(11 - count)) * 2;
			
			//value += (position * 2 + orientation) * (GetFactorial(12) / GetFactorial(6)) + ((GetFactorial(11 - count) / GetFactorial(6)) * count);
			++count;

			//value += ((GetFactorial(i) * position) + (2 * orientation * GetFactorial(11))) / GetFactorial(6);
			//value += (position * 3 + CheckCornerValue(cornerCubies[i], i)) * GetFactorial(i - 1) * 3;
			//value += (threePow * eightFact * orientation) + (position * GetFactorial(i) * threePow); // (3^i * 8! * co_i) + (3^i * cp_i * i!)
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
}