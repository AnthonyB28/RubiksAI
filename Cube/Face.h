#define RUBIKS_KEY "RED 0 GREEN 1 YELLOW 2 BLUE 3 ORANGE 4 WHITE 5 "
#define RED 0
#define GREEN 1
#define YELLOW 2
#define BLUE 3
#define ORANGE 4
#define WHITE 5

namespace Rubiks
{
	class Face
	{
	public:
		Face();
		~Face();
		int * GetCorners(); // Gets the array of corner values
		int * GetEdges(); // Gets the array of edge values

		int ** m_ValuesArrays; // 2D array of face values [row][index]
	};
}