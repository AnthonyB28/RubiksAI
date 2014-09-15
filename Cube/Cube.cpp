#include "Cube.h"

namespace Rubiks
{
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
	
	bool Cube::CheckValidCorners()
	{
		int ** cornerCubies = GetCornerCubies();
		int totalValue = 0;
		for (int i = 0; i < 3; ++i)
		{
			totalValue += CheckCornerValue(cornerCubies[0], i);
			totalValue += CheckCornerValue(cornerCubies[1], i);
			totalValue += CheckCornerValue(cornerCubies[2], i);
			totalValue += CheckCornerValue(cornerCubies[3], i);
			totalValue += CheckCornerValue(cornerCubies[4], i);
			totalValue += CheckCornerValue(cornerCubies[5], i);
			totalValue += CheckCornerValue(cornerCubies[6], i);
			totalValue += CheckCornerValue(cornerCubies[7], i);
		}

		DeleteCornerCubies(cornerCubies);
		bool isValid = true;

		// Total must be divisible by 3
		if (totalValue % 3)
		{
			isValid = false;
		}

		return isValid;
	}

	// correct orientation = 0
	// clockwise = 1
	// anti-clockwise = 2
	int Cube::CheckCornerValue(int cornerValues[3], int index)
	{
		if (cornerValues[index] == WHITE || cornerValues[index] == YELLOW)
		{
			if (index == 0)
			{
				return 1;
			}
			else if (index == 1)
			{
				return 2;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
}