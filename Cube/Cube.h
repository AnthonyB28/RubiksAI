#include "Face.h"

namespace Rubiks
{
	class Cube
	{
	public:
		typedef unsigned int UInt32;
		bool CheckValidParity();

		Rubiks::Face m_Faces[6]; // Rubik's Cube representation - note for assignment each index happens to represent face color!
	
	private :
		
		bool CheckValidPositions(UInt32 ** cornerCubies, UInt32 ** edgeCubies);
		
		UInt32 ** GetCornerCubies(); // RGW - RBW - RGY - RBY - GOW - GOY - YOB - BOW
		void DeleteCornerCubies(UInt32 ** cornerCubies);
		int CheckCornerValue(UInt32 cornerValues[3], int corner);
		int GetCornerPermutationValue(UInt32 cornerCubie[3]);
		bool CheckValidCorners(UInt32 ** cornerCubies);
		
		UInt32 ** GetEdgeCubies(); // RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
		void DeleteEdgeCubies(UInt32 ** edgeCubies);
		int GetEdgePermutationValue(UInt32 edgeCubie[2]);
		bool CheckValidEdges(UInt32 ** edgeCubies);
		bool CheckValidEdgeColors(UInt32 edge[2]);
	};
}