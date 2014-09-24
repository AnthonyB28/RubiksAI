#include "Cube.h"
#include <stdexcept>

namespace Rubiks
{
	// Do our 3 tests to find the 1/12 combinations that can be incorrect
	bool Cube::CheckValidParity()
	{
		int ** cornerCubies = GetCornerCubies();
		int ** edgeCubies = GetEdgeCubies();
		bool isValid = true;

		if (!CheckValidPositions(cornerCubies, edgeCubies) ||
			!CheckValidCorners(cornerCubies) ||
			!CheckValidEdges(edgeCubies))
		{
			isValid = false;
		}

		DeleteCornerCubies(cornerCubies);
		DeleteEdgeCubies(edgeCubies);

		return isValid;
	}

	// Checks for permutation parity
	bool Cube::CheckValidPositions(int ** cornerCubies, int ** edgeCubies)
	{
		int edgePositions[12];
		// Check number of edge swaps
		// RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
		for (int i = 0; i < 12; ++i)
		{
			edgePositions[i] = GetEdgePermutationValue(edgeCubies[i]);
		}

		int edgeInversions = 0;
		for (int begin = 0; begin < 12; ++begin)
		{
			for (int end = begin + 1; end < 12; ++end)
			{
				if (edgePositions[begin] > edgePositions[end])
				{
					++edgeInversions;
				}
			}
		}

		int cornerPositions[8];
		// Check number of corner inversions
		// RGW - RBW - RGY - RBY - GOW - GOY - YOB - BOW
		for (int i = 0; i < 8; ++i)
		{
			cornerPositions[i] = GetCornerPermutationValue(cornerCubies[i]);
		}

		int cornerInversions = 0;
		for (int begin = 0; begin < 8; ++begin)
		{
			for (int end = begin + 1; end < 8; ++end)
			{
				if (cornerPositions[begin] > cornerPositions[end])
				{
					++cornerInversions;
				}
			}
		}

		// Total swaps must be even
		if (((cornerInversions + edgeInversions) & 1) == 0)
		{
			return true;
		}
		else
		{
			return false; // Odd! invalid
		}
	}

	/********************

		CORNER CUBIES

	*******************/

	// Gets a 8x3 array of all corner cubies
	// RGW - RBW - RGY - RBY - GOW - GOY - YOB - BOW
	// DON'T FORGET TO CALL DELETECORNERCUBIES FROM THIS!!
	// TODO make this a class or something
	int ** Cube::GetCornerCubies()
	{
		int * redCorners = m_Faces[0].GetCorners();
		int * greenCorners = m_Faces[1].GetCorners();
		int * yellowCorners = m_Faces[2].GetCorners();
		int * blueCorners = m_Faces[3].GetCorners();
		int * orangeCorners = m_Faces[4].GetCorners();
		int * whiteCorners = m_Faces[5].GetCorners();

		int ** cornerCubies = new int*[8];

		// 8 corners should exist
		cornerCubies[0] = new int[3]{ redCorners[0], greenCorners[0], whiteCorners[2] };
		cornerCubies[1] = new int[3]{ redCorners[1], blueCorners[1], whiteCorners[3] };
		cornerCubies[2] = new int[3]{ redCorners[2], greenCorners[1], yellowCorners[0] };
		cornerCubies[3] = new int[3]{ redCorners[3], blueCorners[0], yellowCorners[1] };
		cornerCubies[4] = new int[3]{ greenCorners[2], orangeCorners[2], whiteCorners[0] };
		cornerCubies[5] = new int[3]{ greenCorners[3], orangeCorners[0], yellowCorners[2] };
		cornerCubies[6] = new int[3]{ blueCorners[2], orangeCorners[1], yellowCorners[3] };
		cornerCubies[7] = new int[3]{ blueCorners[3], orangeCorners[3], whiteCorners[1] };

		delete[] redCorners;
		delete[] greenCorners;
		delete[] yellowCorners;
		delete[] blueCorners;
		delete[] orangeCorners;
		delete[] whiteCorners;

		return cornerCubies;
	}

	// Delete the corner cubies Collection
	void Cube::DeleteCornerCubies(int ** cornerCubies)
	{
		for (int i = 0; i < 8; ++i)
		{
			delete[] cornerCubies[i];
		}
		delete[] cornerCubies;
	}

	int Cube::GetCornerPermutationValue(int cornerCubie[3])
	{
		int x = cornerCubie[0];
		int y = cornerCubie[1];
		int z = cornerCubie[2];

		if ((x == RED && y == GREEN && z == WHITE) ||
			(x == RED && y == WHITE && z == GREEN) ||
			(x == GREEN && y == RED && z == WHITE) ||
			(x == GREEN && y == WHITE && z == RED) ||
			(x == WHITE && y == RED && z == GREEN) ||
			(x == WHITE && y == GREEN && z == RED))
		{
			return 0;
		}
		else if((x == RED && y == BLUE && z == WHITE) ||
				(x == RED && y == WHITE && z == BLUE) ||
				(x == BLUE && y == RED && z == WHITE) ||
				(x == BLUE && y == WHITE && z == RED) ||
				(x == WHITE && y == RED && z == BLUE) ||
				(x == WHITE && y == BLUE && z == RED))
		{
			return 1;
		}
		else if((x == RED && y == GREEN && z == YELLOW) ||
				(x == RED && y == YELLOW && z == GREEN) ||
				(x == YELLOW && y == RED && z == GREEN) ||
				(x == YELLOW && y == GREEN && z == RED) ||
				(x == GREEN && y == RED && z == YELLOW) ||
				(x == GREEN && y == YELLOW && z == RED))
		{
			return 2;
		}
		else if((x == RED && y == BLUE && z == YELLOW) ||
				(x == RED && y == YELLOW && z == BLUE) ||
				(x == BLUE && y == RED && z == YELLOW) ||
				(x == BLUE && y == YELLOW && z == RED) ||
				(x == YELLOW && y == BLUE && z == RED) ||
				(x == YELLOW && y == RED && z == BLUE))
		{
			return 3;
		}
		else if((x == ORANGE && y == GREEN && z == WHITE) ||
				(x == ORANGE && y == WHITE && z == GREEN) ||
				(x == WHITE && y == ORANGE && z == GREEN) ||
				(x == WHITE && y == GREEN && z == ORANGE) ||
				(x == GREEN && y == ORANGE && z == WHITE) ||
				(x == GREEN && y == WHITE && z == ORANGE))
		{
			return 4;
		}
		else if((x == ORANGE && y == GREEN && z == YELLOW) ||
				(x == ORANGE && y == YELLOW && z == GREEN) ||
				(x == YELLOW && y == ORANGE && z == GREEN) ||
				(x == YELLOW && y == GREEN && z == ORANGE) ||
				(x == GREEN && y == ORANGE && z == YELLOW) ||
				(x == GREEN && y == YELLOW && z == ORANGE))
		{
			return 5;
		}
		else if((x == ORANGE && y == BLUE && z == YELLOW) ||
				(x == ORANGE && y == YELLOW && z == BLUE) ||
				(x == YELLOW && y == ORANGE && z == BLUE) ||
				(x == YELLOW && y == BLUE && z == ORANGE) ||
				(x == BLUE && y == ORANGE && z == YELLOW) ||
				(x == BLUE && y == YELLOW && z == ORANGE))
		{
			return 6;
		}

		else if ((x == ORANGE && y == BLUE && z == WHITE) ||
			(x == ORANGE && y == WHITE && z == BLUE) ||
			(x == WHITE && y == ORANGE && z == BLUE) ||
			(x == WHITE && y == BLUE && z == ORANGE) ||
			(x == BLUE && y == ORANGE && z == WHITE) ||
			(x == BLUE && y == WHITE && z == ORANGE))
		{
			return 7;
		}
		else
		{
			// Completely invalid cube?
			throw std::invalid_argument("Corner combination does not exist");
		}
	}

	// correct orientation = 0
	// clockwise = 1
	// anti-clockwise = 2
	int Cube::CheckCornerValue(int cornerValues[3], int corner)
	{
		int x = cornerValues[0];
		int y = cornerValues[1];
		int z = cornerValues[2];
		for (int i = 0; i < 3; ++i)
		{ 
			if (cornerValues[i] == WHITE || cornerValues[i] == YELLOW)
			{
				if (corner == 0 || corner == 3 || corner == 4 || corner == 6)
				{

					if (i == 0)
					{
						return 2;
					}
					else if (i == 1)
					{
						return 1;
					}
				}
				else if (corner == 1 || corner == 2 || corner == 5 || corner == 7)
				{
					if (i == 0)
					{
						return 1;
					}
					else if (i == 1)
					{
						return 2;
					}
				}
			}
		}

		return 0; // Valid position
	}

	// Corner cubie parity test
	bool Cube::CheckValidCorners(int ** cornerCubies)
	{
		int totalValue = 0;

		for (int i = 0; i < 8; ++i)
		{
			totalValue += CheckCornerValue(cornerCubies[i], i);
		}

		bool isValid = true;

		// Total must be divisible by 3
		if (totalValue % 3)
		{
			isValid = false;
		}

		return isValid;
	}

	/*********************

	    EDGE CUBIES

	*********************/

	// Gets a 12x2 array of all edge cubies
	// RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
	// DON'T FORGET TO CALL DELETEEDGECUBIES FROM THIS!!
	// TODO make this a class or something
	int ** Cube::GetEdgeCubies()
	{
		int * redEdges = m_Faces[0].GetEdges();
		int * greenEdges = m_Faces[1].GetEdges();
		int * yellowEdges = m_Faces[2].GetEdges();
		int * blueEdges = m_Faces[3].GetEdges();
		int * orangeEdges = m_Faces[4].GetEdges();
		int * whiteEdges = m_Faces[5].GetEdges();

		int ** edgeCubies = new int*[12];

		// 8 corners should exist
		edgeCubies[0] = new int[2]{ redEdges[0], whiteEdges[3] }; // RW
		edgeCubies[1] = new int[2]{ redEdges[1], greenEdges[0] }; // RG
		edgeCubies[2] = new int[2]{ redEdges[2], blueEdges[0] }; // RB
		edgeCubies[3] = new int[2]{ redEdges[3], yellowEdges[0] }; // RY
		edgeCubies[4] = new int[2]{ greenEdges[1], whiteEdges[1] }; // GW
		edgeCubies[5] = new int[2]{ greenEdges[2], yellowEdges[1] }; // GY
		edgeCubies[6] = new int[2]{ greenEdges[3], orangeEdges[1] }; // GO
		edgeCubies[7] = new int[2]{ yellowEdges[2], blueEdges[1] }; // YB
		edgeCubies[8] = new int[2]{ yellowEdges[3], orangeEdges[0] }; // YO
		edgeCubies[9] = new int[2]{ blueEdges[2], whiteEdges[2] }; // BW
		edgeCubies[10] = new int[2]{ blueEdges[3], orangeEdges[2] }; // BO
		edgeCubies[11] = new int[2]{ orangeEdges[3], whiteEdges[0] }; // OW
		
		delete[] redEdges;
		delete[] greenEdges;
		delete[] yellowEdges;
		delete[] blueEdges;
		delete[] orangeEdges;
		delete[] whiteEdges;

		return edgeCubies;
	}

	// Delete the corner cubies Collection
	void Cube::DeleteEdgeCubies(int ** edgeCubies)
	{
		for (int i = 0; i < 12; ++i)
		{
			delete[] edgeCubies[i];
		}
		delete[] edgeCubies;
	}

	int Cube::GetEdgePermutationValue(int edgeCubie[2])
	{
		int x = edgeCubie[0];
		int y = edgeCubie[1];
		if ((x == RED && y == WHITE) ||
			(x == WHITE && y == RED))
		{
			return 0;
		}
		else if ((x == RED && y == GREEN) ||
			(x == GREEN && y == RED))
		{
			return 1;
		}
		else if ((x == RED && y == BLUE) ||
			(x == BLUE && y == RED))
		{
			return 2;
		}
		else if ((x == RED && y == YELLOW) ||
			(x == YELLOW && y == RED))
		{
			return 3;
		}

		else if ((x == GREEN && y == WHITE) ||
			(x == WHITE && y == GREEN))
		{
			return 4;
		}
		else if ((x == GREEN && y == YELLOW) ||
			(x == YELLOW && y == GREEN))
		{
			return 5;
		}
		else if ((x == GREEN && y == ORANGE) ||
			(x == ORANGE && y == GREEN))
		{
			return 6;
		}
		else if ((x == YELLOW && y == BLUE) ||
			(x == BLUE && y == YELLOW))
		{
			return 7;
		}
		else if ((x == YELLOW && y == ORANGE) ||
			(x == ORANGE && y == YELLOW))
		{
			return 8;
		}
		else if ((x == BLUE && y == WHITE) ||
			(x == WHITE && y == BLUE))
		{
			return 9;
		}
		else if ((x == BLUE && y == ORANGE) ||
			(x == ORANGE && y == BLUE))
		{
			return 10;
		}
		else if ((x == WHITE && y == ORANGE) ||
			(x == ORANGE && y == WHITE))
		{
			return 11;
		} 
		else
		{
			// Completely invalid cube?
			throw std::invalid_argument("Edge combination does not exist");
		}
	}

	// Edge cubie parity test
	bool Cube::CheckValidEdges(int ** edgeCubies)
	{
		// Value of all edge orientations is even
		// LEFT RIGHT TOP AND BOTTOM flips zero edges
		// FRONT AND BACK by 90 degrees flips 4
		// legal move changes value by even number / 2
		// pick edge, n = 0
		// try to bring edge in position where it ought to be in a solved cube
		// using only LEFT RIGHT TOP AND BOTTOM
		// when edge is in position, check wether edge is orientated right.
		// if not, increment by 1
		// if so then do reverse moves
		// check whether all 20 edges checked. If yes, then go to next otherwise go back to a
		// n = total number of flips / 2
		// RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
		int n = 0;
		bool isValid = true;
		for (int i = 0; i < 12; ++i)
		{
			int edgeToValidate[2] = { edgeCubies[i][0], edgeCubies[i][1] };
			if (CheckValidEdgeColors(edgeToValidate))
			{
				if (i == 0) // RW
				{
					if (edgeToValidate[0] == WHITE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
				}
				else if (i == 1) // RG
				{
					if (edgeToValidate[0] == GREEN && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == WHITE)
					{
						++n;
					}
				}
				else if (i == 2) // RB
				{
					if (edgeToValidate[0] == RED && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == WHITE)
					{
						++n;
					}

				}
				else if (i == 3) // RY
				{
					if (edgeToValidate[0] == WHITE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
				}
				else if (i == 4) // GW
				{
					if (edgeToValidate[0] == WHITE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
				}
				else if (i == 5) // GY
				{
					if (edgeToValidate[0] == WHITE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
				}
				else if (i == 6) // GO
				{
					if (edgeToValidate[0] == WHITE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
				}
				else if (i == 7) // YB
				{
					if (edgeToValidate[0] == RED && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == WHITE)
					{
						++n;
					}
				}
				else if (i == 8) // YO
				{
					if (edgeToValidate[0] == RED && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == GREEN && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == YELLOW)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == WHITE)
					{
						++n;
					}
					else if (edgeToValidate[0] == BLUE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == WHITE)
					{
						++n;
					}
				}
				else if (i == 9) // BW
				{
					if (edgeToValidate[0] == WHITE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
				}
				else if (i == 10) // BO
				{
					if (edgeToValidate[0] == WHITE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
				}
				else if (i == 11) // OW
				{
					if (edgeToValidate[0] == WHITE && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == RED && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == RED)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == GREEN)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == YELLOW && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == ORANGE && edgeToValidate[1] == BLUE)
					{
						++n;
					}
					else if (edgeToValidate[0] == WHITE && edgeToValidate[1] == ORANGE)
					{
						++n;
					}
				}
			}
			else
			{
				isValid = false;
				break;
			}
		}

		// Valid parity is even
		if ((n & 1) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Edges are either one of two color combinations
	bool Cube::CheckValidEdgeColors(int edge[2])
	{
		if (
			(edge[0] == RED && edge[1] == WHITE) || (edge[0] == WHITE && edge[1] == RED) ||
			(edge[0] == RED && edge[1] == BLUE) || (edge[0] == BLUE && edge[1] == RED) ||
			(edge[0] == RED && edge[1] == GREEN) || (edge[0] == GREEN && edge[1] == RED) ||
			(edge[0] == RED && edge[1] == YELLOW) || (edge[0] == YELLOW && edge[1] == RED) ||
			(edge[0] == GREEN && edge[1] == WHITE) || (edge[0] == WHITE && edge[1] == GREEN) ||
			(edge[0] == GREEN && edge[1] == YELLOW) || (edge[0] == YELLOW && edge[1] == GREEN) ||
			(edge[0] == GREEN && edge[1] == ORANGE) || (edge[0] == ORANGE && edge[1] == GREEN) ||
			(edge[0] == YELLOW && edge[1] == BLUE) || (edge[0] == BLUE && edge[1] == YELLOW) ||
			(edge[0] == YELLOW && edge[1] == ORANGE) || (edge[0] == ORANGE && edge[1] == YELLOW) ||
			(edge[0] == BLUE && edge[1] == WHITE) || (edge[0] == WHITE && edge[1] == BLUE) ||
			(edge[0] == BLUE && edge[1] == ORANGE) || (edge[0] == ORANGE && edge[1] == BLUE) ||
			(edge[0] == ORANGE && edge[1] == WHITE) || (edge[0] == WHITE && edge[1] == ORANGE)
			)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}
