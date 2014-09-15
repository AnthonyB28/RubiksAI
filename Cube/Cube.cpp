#include "Cube.h"

namespace Rubiks
{
	bool Cube::CheckValidCorners()
	{
		int * redCorners = m_Faces[0].GetCorners();
		int * greenCorners = m_Faces[1].GetCorners();
		int * yellowCorners = m_Faces[2].GetCorners();
		int * blueCorners = m_Faces[3].GetCorners();
		int * orangeCorners = m_Faces[4].GetCorners();
		int * whiteCorners = m_Faces[5].GetCorners();

		int ** cornerCombos;
		int * cornersCombosArray[8];
		cornerCombos = cornersCombosArray;
		// 8 corners should exist
		// RGW - RBW - RGY - RBY - GOW - GOY - YOB - BOW
		int RGW[3] = { redCorners[0], greenCorners[0], whiteCorners[2] };
		int RBW[3] = { redCorners[1], blueCorners[1], whiteCorners[3] };
		int RGY[3] = { redCorners[2], greenCorners[1], yellowCorners[0] };
		int RBY[3] = { redCorners[3], blueCorners[0], yellowCorners[1] };
		int GOW[3] = { greenCorners[2], orangeCorners[2], whiteCorners[0] };
		int GOY[3] = { greenCorners[3], orangeCorners[0], yellowCorners[2] };
		int YOB[3] = { yellowCorners[3], orangeCorners[1], blueCorners[2] };
		int BOW[3] = { blueCorners[3], orangeCorners[3], whiteCorners[1] };

		cornerCombos[0] = RGW;
		cornerCombos[1] = RBW;
		cornerCombos[2] = RGY;
		cornerCombos[3] = RBY;
		cornerCombos[4] = GOW;
		cornerCombos[5] = GOY;
		cornerCombos[6] = YOB;
		cornerCombos[7] = BOW;

		bool isValid = true;

		return isValid;
	}
}