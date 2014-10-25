#include "Cube.h"

namespace Rubiks
{
	// Do our 3 tests to find the 1/12 combinations that can be incorrect
	bool Cube::CheckValidParity()
	{
		UInt32 ** cornerCubies = GetCornerCubies();
		UInt32 ** edgeCubies = GetEdgeCubies();
		bool isValid = true;

		if (!CheckPermutations(cornerCubies, edgeCubies) ||
			!CheckCornerParity(cornerCubies) ||
			!CheckEdgeParity(edgeCubies))
		{
			isValid = false;
		}

		DeleteCornerCubies(cornerCubies);
		DeleteEdgeCubies(edgeCubies);

		return isValid;
	}

	// Checks for permutation parity
	bool Cube::CheckPermutations(UInt32 ** cornerCubies, UInt32 ** edgeCubies)
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
			if (!CheckValidCornerColors(cornerCubies[i], i))
			{
				return false;
			}
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
	Cube::UInt32 ** Cube::GetCornerCubies()
	{
		CornerCubies redCorners = m_Faces[0].GetCorners();
		CornerCubies greenCorners = m_Faces[1].GetCorners();
		CornerCubies yellowCorners = m_Faces[2].GetCorners();
		CornerCubies blueCorners = m_Faces[3].GetCorners();
		CornerCubies orangeCorners = m_Faces[4].GetCorners();
		CornerCubies whiteCorners = m_Faces[5].GetCorners();

		UInt32 ** cornerCubies = new UInt32*[8];

		// 8 corners should exist
		cornerCubies[0] = new UInt32[3]{ redCorners.x, greenCorners.x, whiteCorners.z };
		cornerCubies[1] = new UInt32[3]{ redCorners.y, blueCorners.y, whiteCorners.w };
		cornerCubies[2] = new UInt32[3]{ redCorners.z, greenCorners.y, yellowCorners.x };
		cornerCubies[3] = new UInt32[3]{ redCorners.w, blueCorners.x, yellowCorners.y };
		cornerCubies[4] = new UInt32[3]{ greenCorners.z, orangeCorners.z, whiteCorners.x };
		cornerCubies[5] = new UInt32[3]{ greenCorners.w, orangeCorners.x, yellowCorners.z };
		cornerCubies[6] = new UInt32[3]{ blueCorners.z, orangeCorners.y, yellowCorners.w };
		cornerCubies[7] = new UInt32[3]{ blueCorners.w, orangeCorners.w, whiteCorners.y };

		return cornerCubies;
	}

	// Delete the corner cubies Collection
	void Cube::DeleteCornerCubies(UInt32 ** cornerCubies)
	{
		for (int i = 0; i < 8; ++i)
		{
			delete[] cornerCubies[i];
		}
		delete[] cornerCubies;
	}

	int Cube::GetCornerPermutationValue(UInt32 cornerCubie[3])
	{
		UInt32 x = cornerCubie[0];
		UInt32 y = cornerCubie[1];
		UInt32 z = cornerCubie[2];

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
			return 0;
			printf("invalid cube");
		}
	}

	// correct orientation = 0
	// clockwise = 1
	// anti-clockwise = 2
	int Cube::GetCornerOrientationValue(UInt32 cornerValues[3], int corner)
	{
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
	bool Cube::CheckCornerParity(UInt32 ** cornerCubies)
	{
		int totalValue = 0;

		for (int i = 0; i < 8; ++i)
		{
			totalValue += GetCornerOrientationValue(cornerCubies[i], i);
		}

		bool isValid = true;

		// Total must be divisible by 3
		if (totalValue % 3)
		{
			isValid = false;
		}

		return isValid;
	}

	// Check to make sure corner colors are valid
	// RGW - RBW - RGY - RBY - GOW - GOY - YOB - BOW
	bool Cube::CheckValidCornerColors(UInt32 cornerCubie[3], int corner)
	{
		if (corner == 0 || corner == 3 || corner == 4 || corner == 6)
		{
			if ((cornerCubie[0] == RED && cornerCubie[1] == GREEN && cornerCubie[2] == WHITE) || //RWG
				(cornerCubie[0] == WHITE && cornerCubie[1] == RED && cornerCubie[2] == GREEN) ||
				(cornerCubie[0] == GREEN && cornerCubie[1] == WHITE && cornerCubie[2] == RED))
			{
				return true;
			}
			else if ((cornerCubie[0] == GREEN && cornerCubie[1] == ORANGE && cornerCubie[2] == WHITE) || // GOW
					(cornerCubie[0] == WHITE && cornerCubie[1] == GREEN && cornerCubie[2] == ORANGE) ||
					(cornerCubie[0] == ORANGE && cornerCubie[1] == WHITE && cornerCubie[2] == GREEN))
			{
				return true;
			}
			else if ((cornerCubie[0] == ORANGE && cornerCubie[1] == BLUE && cornerCubie[2] == WHITE) || //OBW
					(cornerCubie[0] == WHITE && cornerCubie[1] == ORANGE && cornerCubie[2] == BLUE) ||
					(cornerCubie[0] == BLUE && cornerCubie[1] == WHITE && cornerCubie[2] == ORANGE))
			{
				return true;
			}
			else if ((cornerCubie[0] == BLUE && cornerCubie[1] == RED && cornerCubie[2] == WHITE) || //BRW
					(cornerCubie[0] == WHITE && cornerCubie[1] == BLUE && cornerCubie[2] == RED) ||
					(cornerCubie[0] == RED && cornerCubie[1] == WHITE && cornerCubie[2] == BLUE))
			{
				return true;
			}
			else if ((cornerCubie[0] == YELLOW && cornerCubie[1] == GREEN && cornerCubie[2] == RED) || //YGR
					(cornerCubie[0] == RED && cornerCubie[1] == YELLOW && cornerCubie[2] == GREEN) ||
					(cornerCubie[0] == GREEN && cornerCubie[1] == RED && cornerCubie[2] == YELLOW))
			{
				return true;
			}
			else if ((cornerCubie[0] == ORANGE && cornerCubie[1] == GREEN && cornerCubie[2] == YELLOW) || //OGY
				(cornerCubie[0] == YELLOW && cornerCubie[1] == ORANGE && cornerCubie[2] == GREEN) ||
				(cornerCubie[0] == GREEN && cornerCubie[1] == YELLOW && cornerCubie[2] == ORANGE))
			{
				return true;
			}
			else if ((cornerCubie[0] == BLUE && cornerCubie[1] == ORANGE && cornerCubie[2] == YELLOW) || // YOB
				(cornerCubie[0] == YELLOW && cornerCubie[1] == BLUE && cornerCubie[2] == ORANGE) ||
				(cornerCubie[0] == ORANGE && cornerCubie[1] == YELLOW && cornerCubie[2] == BLUE))
			{
				return true;
			}
			else if ((cornerCubie[0] == BLUE && cornerCubie[1] == YELLOW && cornerCubie[2] == RED) || //RYB
				(cornerCubie[0] == RED && cornerCubie[1] == BLUE && cornerCubie[2] == YELLOW) ||
				(cornerCubie[0] == YELLOW && cornerCubie[1] == RED && cornerCubie[2] == BLUE))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (corner == 1 || corner == 2 || corner == 5)
		{
			if ((cornerCubie[0] == GREEN && cornerCubie[1] == RED && cornerCubie[2] == WHITE) || //RWG
				(cornerCubie[0] == WHITE && cornerCubie[1] == GREEN && cornerCubie[2] == RED) ||
				(cornerCubie[0] == RED && cornerCubie[1] == WHITE && cornerCubie[2] == GREEN))
			{
				return true;
			}
			else if ((cornerCubie[0] == ORANGE && cornerCubie[1] == GREEN && cornerCubie[2] == WHITE) || // GOW
				(cornerCubie[0] == WHITE && cornerCubie[1] == ORANGE && cornerCubie[2] == GREEN) ||
				(cornerCubie[0] == GREEN && cornerCubie[1] == WHITE && cornerCubie[2] == ORANGE))
			{
				return true;
			}
			else if ((cornerCubie[0] == BLUE && cornerCubie[1] == ORANGE && cornerCubie[2] == WHITE) || //OBW
				(cornerCubie[0] == WHITE && cornerCubie[1] == BLUE && cornerCubie[2] == ORANGE) ||
				(cornerCubie[0] == ORANGE && cornerCubie[1] == WHITE && cornerCubie[2] == BLUE))
			{
				return true;
			}
			else if ((cornerCubie[0] == RED && cornerCubie[1] == BLUE && cornerCubie[2] == WHITE) || //BRW
				(cornerCubie[0] == WHITE && cornerCubie[1] == RED && cornerCubie[2] == BLUE) ||
				(cornerCubie[0] == BLUE && cornerCubie[1] == WHITE && cornerCubie[2] == RED))
			{
				return true;
			}
			else if ((cornerCubie[0] == YELLOW && cornerCubie[1] == RED && cornerCubie[2] == GREEN) || //YGR
				(cornerCubie[0] == GREEN && cornerCubie[1] == YELLOW && cornerCubie[2] == RED) ||
				(cornerCubie[0] == RED && cornerCubie[1] == GREEN && cornerCubie[2] == YELLOW))
			{
				return true;
			}
			else if ((cornerCubie[0] == GREEN && cornerCubie[1] == ORANGE && cornerCubie[2] == YELLOW) || //OGY
				(cornerCubie[0] == YELLOW && cornerCubie[1] == GREEN && cornerCubie[2] == ORANGE) ||
				(cornerCubie[0] == ORANGE && cornerCubie[1] == YELLOW && cornerCubie[2] == GREEN))
			{
				return true;
			}
			else if ((cornerCubie[0] == ORANGE && cornerCubie[1] == BLUE && cornerCubie[2] == YELLOW) || // YOB
				(cornerCubie[0] == YELLOW && cornerCubie[1] == ORANGE && cornerCubie[2] == BLUE) ||
				(cornerCubie[0] == BLUE && cornerCubie[1] == YELLOW && cornerCubie[2] == ORANGE))
			{
				return true;
			}
			else if ((cornerCubie[0] == RED && cornerCubie[1] == YELLOW && cornerCubie[2] == BLUE) || //RYB
				(cornerCubie[0] == BLUE && cornerCubie[1] == RED && cornerCubie[2] == YELLOW) ||
				(cornerCubie[0] == YELLOW && cornerCubie[1] == BLUE && cornerCubie[2] == RED))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	/*********************

	    EDGE CUBIES

	*********************/

	// Gets a 12x2 array of all edge cubies
	// RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
	// DON'T FORGET TO CALL DELETEEDGECUBIES FROM THIS!!
	// TODO make this a class or something
	Cube::UInt32 ** Cube::GetEdgeCubies()
	{
		EdgeCubies redEdges = m_Faces[0].GetEdges();
		EdgeCubies greenEdges = m_Faces[1].GetEdges();
		EdgeCubies yellowEdges = m_Faces[2].GetEdges();
		EdgeCubies blueEdges = m_Faces[3].GetEdges();
		EdgeCubies orangeEdges = m_Faces[4].GetEdges();
		EdgeCubies whiteEdges = m_Faces[5].GetEdges();

		UInt32 ** edgeCubies = new UInt32*[12];

		// 8 corners should exist
		edgeCubies[0] = new UInt32[2]{ redEdges.x, whiteEdges.w }; // RW
		edgeCubies[1] = new UInt32[2]{ redEdges.y, greenEdges.x }; // RG
		edgeCubies[2] = new UInt32[2]{ redEdges.z, blueEdges.x }; // RB
		edgeCubies[3] = new UInt32[2]{ redEdges.w, yellowEdges.x }; // RY
		edgeCubies[4] = new UInt32[2]{ greenEdges.y, whiteEdges.y }; // GW
		edgeCubies[5] = new UInt32[2]{ greenEdges.z, yellowEdges.y }; // GY
		edgeCubies[6] = new UInt32[2]{ greenEdges.w, orangeEdges.y }; // GO
		edgeCubies[7] = new UInt32[2]{ yellowEdges.z, blueEdges.y }; // YB
		edgeCubies[8] = new UInt32[2]{ yellowEdges.w, orangeEdges.x }; // YO
		edgeCubies[9] = new UInt32[2]{ blueEdges.z, whiteEdges.z }; // BW
		edgeCubies[10] = new UInt32[2]{ blueEdges.w, orangeEdges.z }; // BO
		edgeCubies[11] = new UInt32[2]{ orangeEdges.w, whiteEdges.x }; // OW

		return edgeCubies;
	}

	// Delete the corner cubies Collection
	void Cube::DeleteEdgeCubies(UInt32 ** edgeCubies)
	{
		for (int i = 0; i < 12; ++i)
		{
			delete[] edgeCubies[i];
		}
		delete[] edgeCubies;
	}

	int Cube::GetEdgePermutationValue(UInt32 edgeCubie[2])
	{
		UInt32 x = edgeCubie[0];
		UInt32 y = edgeCubie[1];
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
			return 0;
		}
	}

	// Edge cubie parity test
	bool Cube::CheckEdgeParity(UInt32 ** edgeCubies)
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
		for (int i = 0; i < 12; ++i)
		{
			UInt32 edgeToValidate[2] = { edgeCubies[i][0], edgeCubies[i][1] };
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
				return false;
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

	int Cube::GetEdgeOrientationValue(UInt32 edgeCubie[2], int i)
	{
		if (i == 0) // RW
		{
			if (edgeCubie[0] == WHITE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
		}
		else if (i == 1) // RG
		{
			if (edgeCubie[0] == GREEN && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == WHITE)
			{
				return 1;
			}
		}
		else if (i == 2) // RB
		{
			if (edgeCubie[0] == RED && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == WHITE)
			{
				return 1;
			}

		}
		else if (i == 3) // RY
		{
			if (edgeCubie[0] == WHITE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
		}
		else if (i == 4) // GW
		{
			if (edgeCubie[0] == WHITE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
		}
		else if (i == 5) // GY
		{
			if (edgeCubie[0] == WHITE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
		}
		else if (i == 6) // GO
		{
			if (edgeCubie[0] == WHITE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
		}
		else if (i == 7) // YB
		{
			if (edgeCubie[0] == RED && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == WHITE)
			{
				return 1;
			}
		}
		else if (i == 8) // YO
		{
			if (edgeCubie[0] == RED && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == GREEN && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == YELLOW)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == WHITE)
			{
				return 1;
			}
			else if (edgeCubie[0] == BLUE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == WHITE)
			{
				return 1;
			}
		}
		else if (i == 9) // BW
		{
			if (edgeCubie[0] == WHITE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
		}
		else if (i == 10) // BO
		{
			if (edgeCubie[0] == WHITE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
		}
		else if (i == 11) // OW
		{
			if (edgeCubie[0] == WHITE && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == RED && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == RED)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == GREEN)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == YELLOW && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == ORANGE && edgeCubie[1] == BLUE)
			{
				return 1;
			}
			else if (edgeCubie[0] == WHITE && edgeCubie[1] == ORANGE)
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}

	// Edges are either one of two color combinations
	bool Cube::CheckValidEdgeColors(UInt32 edge[2])
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
