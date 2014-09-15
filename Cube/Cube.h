#include "Face.h"
#include <string>

namespace Rubiks
{
	class Cube
	{
	public:
		bool CheckValidCorners();
		
		Rubiks::Face m_Faces[6]; // Rubik's Cube representation - note for assignment each index happens to represent face color!
	
	private :
		int CheckCornerValue(int test[3], int index);
		int ** GetCornerCubies();
		void DeleteCornerCubies(int ** cornerCubies);
	};
}