#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable: 4244)
#include "Cube.h"
#include <queue>
#include <iostream>
#include <fstream>

namespace Rubiks
{
	struct Cube::State
	{
		// Each Cube state is only ~22 bytes!
		State(int moveCount, Cube const & cube)
			: m_PreviousMove(30) // 30 is a placeholder so we don't skip the goal state at 0
			, m_MoveCount(moveCount)
			, m_Cube(cube)
		{}

		unsigned int m_PreviousMove : 5; // 0 - 32
		unsigned int m_MoveCount : 4; // Total # of moves to this position
		Cube m_Cube;
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

	void Cube::TestTableFileRead(char const * const fileName, bool const corners)
	{
		std::fstream file;
		file.open(fileName, std::ios::binary | std::ios::in);
		unsigned long long maxHash = 0;
		if (corners)
		{
			maxHash = UNIQUE_CORNERS / 2;
		}
		else
		{
			maxHash = UNIQUE_EDGES / 2;
		}
		std::vector<unsigned int> numCounts{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		for (int hash = 0; hash < maxHash; ++hash)
		{
			unsigned long long hash1 = hash * 2;
			unsigned long long hash2 = hash * 2 + 1;
			file.seekg(hash);
			char byteNum;
			file.read(&byteNum, sizeof(char));
			unsigned char testing = (unsigned char)byteNum;
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

	void Cube::TableFileLoad(char const * const fileName, std::vector<char>& map)
	{
		std::fstream file;
		file.open(fileName, std::ios::binary | std::ios::in);
		file.seekg(0);
		file.read((char*)&map[0], map.size());
		file.close();
	}

	int GetThreePow(int num)
	{
		if (num == 0) { return 1; }
		else if (num == 1) { return 3; }
		else if (num == 2) { return 9; }
		else if (num == 3) { return 27; }
		else if (num == 4) { return 81; }
		else if (num == 5) { return 243; }
		else if (num == 6) { return 729; }
		else return num  * GetThreePow(num);
	}

	// Up to 12 is precomputed
	int GetFactorial(int num)
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

	// Generates a hash table for all the unique states of corners for a given hueristic, and writes it to a file. 
	// Heuristic shouldnt be larger than 12
	void Cube::GenerateCornerTables(int const heuristic)
	{
		if (heuristic > 12)
		{
			printf("\n Too large of heuristic to generate Corner Tables.");
			return;
		}

		std::vector<int> *uniqueStates = new std::vector < int > ;
		uniqueStates->resize(UNIQUE_CORNERS, -1);
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
		for (int hash = 0; hash < UNIQUE_CORNERS; hash += 2)
		{
			// Always do even.
			if (uniqueStates->at(hash) != -1)
			{
				unsigned long long byteLoc = hash;
				byteLoc /= 2; // Always an even number.
				char moveByte;
				moveByte = uniqueStates->at(hash) << 4; // Store our first number as normal.
				if (hash + 1 < UNIQUE_CORNERS) // prevent overflow
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
	unsigned long long Cube::GetCornerHash() const
	{
		unsigned long long value = 1;
		// inlining this shaves off several seconds of speed!
		UInt32 corner0[3]; GetCornerCubie(0, corner0);
		UInt32 corner1[3]; GetCornerCubie(1, corner1);
		UInt32 corner2[3]; GetCornerCubie(2, corner2);
		UInt32 corner3[3]; GetCornerCubie(3, corner3);
		UInt32 corner4[3]; GetCornerCubie(4, corner4);
		UInt32 corner5[3]; GetCornerCubie(5, corner5);
		UInt32 corner6[3]; GetCornerCubie(6, corner6);
		UInt32 corner7[3]; GetCornerCubie(7, corner7);
		UInt32* cornerCubies[8] = { corner0, corner1, corner2, corner3, corner4, corner5, corner6, corner7 };

		int cornerValue0 = GetCornerPermutationValue(corner0);
		int cornerValue1 = GetCornerPermutationValue(corner1);
		int cornerValue2 = GetCornerPermutationValue(corner2);
		int cornerValue3 = GetCornerPermutationValue(corner3);
		int cornerValue4 = GetCornerPermutationValue(corner4);
		int cornerValue5 = GetCornerPermutationValue(corner5);
		int cornerValue6 = GetCornerPermutationValue(corner6);
		int cornerValue7 = GetCornerPermutationValue(corner7);
		// From corners 0 to 7, stores the value of cubies
		int cubePositions [8] = { cornerValue0, cornerValue1, cornerValue2, cornerValue3, cornerValue4, cornerValue5, cornerValue6, cornerValue7 };
		for (int i = 0; i < 7; ++i) // For each corner cubie VALUE (eg RYG = 0)
		{
			int positionVal;
			int posOffset = 0;
			for (int index = 0; index < 8; ++index)
			{
				if (cubePositions[index] == -1)
				{
					++posOffset;
				}
				else if (cubePositions[index] == i)
				{
					cubePositions[index] = -1;
					positionVal = index - posOffset;
					break;
				}
			}
			int absPosition;
			if (i == cornerValue0) { absPosition = 0; }
			else if (i == cornerValue1) { absPosition = 1; }
			else if (i == cornerValue2) { absPosition = 2; }
			else if (i == cornerValue3) { absPosition = 3; }
			else if (i == cornerValue4) { absPosition = 4; }
			else if (i == cornerValue5) { absPosition = 5; }
			else if (i == cornerValue6) { absPosition = 6; }
			else { absPosition = 7; }
			int threePow = GetThreePow(i);
			int orientation = GetCornerOrientationValue(cornerCubies[absPosition], absPosition); // Check the cubie orientation in its actual position.
			value += (positionVal * 3 + orientation) * (GetFactorial(8) / GetFactorial(8 - i)) * threePow; //(cp_i * 3 + co_i) * (8! / 8-i!) * 3^i
		}
// 		static unsigned long long largestValue = 0;
// 		if (value > largestValue)
// 		{
// 			largestValue = value;
// 			printf("\n%d", largestValue);
// 		}
		return value;
	}


	// Generates a hash table for all the unique states of one set of edges for a given hueristic, and writes it to a file.
	// Heuristic shouldnt be larger than 11
	void Cube::GenerateEdgeTables(int const heuristic, bool const setA)
	{
		if (heuristic > 11)
		{
			printf("\nHeuristic too large for edge tables");
			return;
		}

		std::vector<int> *uniqueStates = new std::vector < int > ;
		uniqueStates->resize(UNIQUE_EDGES, -1);
		std::queue<State*> q;
		q.push(new State(0, Cube::GetGoalCube())); // start with goal state
		uniqueStates->at(q.front()->m_Cube.GetEdgeHash(setA)) = 0; // Make sure we save the goal state's value
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

						unsigned long long hash = newState->m_Cube.GetEdgeHash(setA);
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
		file.open("Edges2.bin", std::ios::binary | std::ios::out | std::ios::trunc);
		unsigned long long missed = 0;
		for (int hash = 0; hash < UNIQUE_EDGES; hash += 2)
		{
			if (uniqueStates->at(hash) != -1)
			{
				unsigned long long byteLoc = hash;
				byteLoc /= 2; // Always an even number.
				char moveByte;
				unsigned int moveCount1 = uniqueStates->at(hash);
				moveByte = moveCount1 << 4; // Store our first number as normal.
				if (hash + 1 < UNIQUE_EDGES) // prevent overflow
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
	unsigned long long Cube::GetEdgeHash(bool const setA) const
	{
		unsigned long long value = 1;
		// inlining this shaves off several seconds of speed!
		UInt32 edge0[2]; GetEdgeCubie(0, edge0);
		UInt32 edge1[2]; GetEdgeCubie(1, edge1);
		UInt32 edge2[2]; GetEdgeCubie(2, edge2);
		UInt32 edge3[2]; GetEdgeCubie(3, edge3);
		UInt32 edge4[2]; GetEdgeCubie(4, edge4);
		UInt32 edge5[2]; GetEdgeCubie(5, edge5);
		UInt32 edge6[2]; GetEdgeCubie(6, edge6);
		UInt32 edge7[2]; GetEdgeCubie(7, edge7);
		UInt32 edge8[2]; GetEdgeCubie(8, edge8);
		UInt32 edge9[2]; GetEdgeCubie(9, edge9);
		UInt32 edge10[2]; GetEdgeCubie(10, edge10);
		UInt32 edge11[2]; GetEdgeCubie(11, edge11);
		UInt32* edgeCubies[12] = { edge0, edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10, edge11 };
		int edgeValue0 = GetEdgePermutationValue(edgeCubies[0]);
		int edgeValue1 = GetEdgePermutationValue(edgeCubies[1]);
		int edgeValue2 = GetEdgePermutationValue(edgeCubies[2]);
		int edgeValue3 = GetEdgePermutationValue(edgeCubies[3]);
		int edgeValue4 = GetEdgePermutationValue(edgeCubies[4]);
		int edgeValue5 = GetEdgePermutationValue(edgeCubies[5]);
		int edgeValue6 = GetEdgePermutationValue(edgeCubies[6]);
		int edgeValue7 = GetEdgePermutationValue(edgeCubies[7]);
		int edgeValue8 = GetEdgePermutationValue(edgeCubies[8]);
		int edgeValue9 = GetEdgePermutationValue(edgeCubies[9]);
		int edgeValue10 = GetEdgePermutationValue(edgeCubies[10]);
		int edgeValue11 = GetEdgePermutationValue(edgeCubies[11]);
		int cubePositions [12] = { edgeValue0, edgeValue1, edgeValue2, edgeValue3, edgeValue4, edgeValue5, edgeValue6, edgeValue7, edgeValue8, edgeValue9, edgeValue10, edgeValue11 };
		int i = 0;
		int maxI = 6;
		int cubieOffSet = 0; // Independent from i because of dual edge sets.
		if (!setA)
		{
			i = 6;
			maxI = 12;
		}
		for (; i < maxI; ++i) // i is the Cubie edge value (e.g i = RW cubie)
		{
			int position;
			int posOffset = 0;
			for (int index = 0; index < 12; ++index)
			{
				if (cubePositions[index] == -1)
				{
					++posOffset;
				}
				else if (cubePositions[index] == i)
				{
					cubePositions[index] = -1;
					position = index - posOffset;
					break;
				}
			}
			int absPosition;
			if (i == edgeValue0) { absPosition = 0; }
			else if (i == edgeValue1) { absPosition = 1; }
			else if (i == edgeValue2) { absPosition = 2; }
			else if (i == edgeValue3) { absPosition = 3; }
			else if (i == edgeValue4) { absPosition = 4; }
			else if (i == edgeValue5) { absPosition = 5; }
			else if (i == edgeValue6) { absPosition = 6; }
			else if (i == edgeValue7) { absPosition = 7; }
			else if (i == edgeValue8) { absPosition = 8; }
			else if (i == edgeValue9) { absPosition = 9; }
			else if (i == edgeValue10) { absPosition = 10; }
			else { absPosition = 11; } // Where is this cubie in our cornerCubies collection!
			int orientation = GetEdgeOrientationValue(edgeCubies[absPosition], absPosition); // We want the orientation of cubie i at its position
			int twoPow =  1 <<  (5-cubieOffSet);
			// (p * 2 + o) * (12-count!/ 6!) * 2
			value += (position * 2 + orientation) * ((GetFactorial(11 - cubieOffSet) / GetFactorial(6)) * twoPow);
			++cubieOffSet;
		}
// 		static unsigned long long largestValue = 0;
// 		if (value > largestValue)
// 		{
// 			largestValue = value;
// 			printf("\n%d", largestValue);
// 		}
		return value;
	}
}