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
		bool CheckValidCorners(int ** cornerCubies);
		int CheckCornerValue(int cornerValues[3], int corner);

		
		int ** GetEdgeCubies(); // RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
		void DeleteEdgeCubies(int ** edgeCubies);
		bool CheckValidEdges(int ** edgeCubies);
		bool CheckValidEdgePair(int edge[2]);
	};
}