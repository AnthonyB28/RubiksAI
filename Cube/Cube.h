#include "Face.h"
#include <string>

namespace Rubiks
{
	class Cube
	{
	public:
		bool CheckValidCorners();
		int ** GetCornerCubies();
		int CheckCornerValue(int test[3], int index);
		Rubiks::Face m_Faces[6]; // Rubik's Cube representation - note for assignment each index happens to represent face color!
	};
}