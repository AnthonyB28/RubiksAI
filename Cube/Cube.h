#include "Face.h"

namespace Rubiks
{
	class Cube
	{
	public:
		typedef unsigned int UInt32;
		bool CheckValidParity();

		// "RED 0 GREEN 1 YELLOW 2 BLUE 3 ORANGE 4 WHITE 5 "
		Rubiks::Face m_Faces[6]; // Rubik's Cube representation - note for assignment each index happens to represent face color!
		void TurnTopCW();
		void TurnTopACW();
		void TurnBottomCW();
		void TurnBottomACW();
		void TurnRightCW();
		void TurnRightACW();
		void TurnLeftCW();
		void TurnLeftACW();
		void TurnFrontAC();
		void TurnFrontACW();
		void TurnBackAC();
		void TurnBackACW();

	private :
		
		bool CheckPermutations(UInt32 ** cornerCubies, UInt32 ** edgeCubies);
		
		UInt32 ** GetCornerCubies(); // RGW - RBW - RGY - RBY - GOW - GOY - YOB - BOW
		void DeleteCornerCubies(UInt32 ** cornerCubies);
		int CheckCornerValue(UInt32 cornerValues[3], int corner);
		int GetCornerPermutationValue(UInt32 cornerCubie[3]);
		bool CheckCornerParity(UInt32 ** cornerCubies);
		bool CheckValidCornerColors(UInt32 cornerCubie[3], int corner);
		
		UInt32 ** GetEdgeCubies(); // RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
		void DeleteEdgeCubies(UInt32 ** edgeCubies);
		int GetEdgePermutationValue(UInt32 edgeCubie[2]);
		bool CheckEdgeParity(UInt32 ** edgeCubies);
		bool CheckValidEdgeColors(UInt32 edge[2]);
	};
}