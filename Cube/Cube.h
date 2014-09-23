#include "Face.h"
#include <string>

namespace Rubiks
{
	class Cube
	{
	public:
		bool CheckValidParity();

		Rubiks::Face m_Faces[6]; // Rubik's Cube representation - note for assignment each index happens to represent face color!
	
	private :
		bool CheckValidPositions(int ** cornerCubies, int ** edgeCubies);
		
		int ** GetCornerCubies(); // RGW - RBW - RGY - RBY - GOW - GOY - YOB - BOW
		void DeleteCornerCubies(int ** cornerCubies);
		int CheckCornerValue(int cornerValues[3], int corner);
		int GetCornerPermutationValue(int cornerCubie[3]);
		bool CheckValidCorners(int ** cornerCubies);
		
		int ** GetEdgeCubies(); // RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
		void DeleteEdgeCubies(int ** edgeCubies);
		int GetEdgePermutationValue(int edgeCubie[2]);
		bool CheckValidEdges(int ** edgeCubies);
		bool CheckValidEdgeColors(int edge[2]);
	};
}