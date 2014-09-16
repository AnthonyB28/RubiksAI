#include "Face.h"
#include <string>

namespace Rubiks
{
	class Cube
	{
	public:
		bool CheckValidCorners();
		bool CheckValidEdges();
		Rubiks::Face m_Faces[6]; // Rubik's Cube representation - note for assignment each index happens to represent face color!
	
	private :
		int CheckCornerValue(int cornerValues[3], int index);
		int ** GetCornerCubies();
		void DeleteCornerCubies(int ** cornerCubies);

		int ** GetEdgeCubies();
		void DeleteEdgeCubies(int ** edgeCubies);
		// RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW1
		bool CheckValidEdgePair(int edge[2]);
	};
}