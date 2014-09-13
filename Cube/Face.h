#define RUBIKS_WIDTH 3
#define RUBIKS_MAXCOLORCOUNT RUBIKS_WIDTH*RUBIKS_WIDTH
#define RUBIKS_KEY "RED 0 BLUE 1 GREEN 2 YELLOW 3 ORANGE 4 WHITE 5 "
#define RED 0
#define BLUE 1
#define GREEN 2
#define YELLOW 3
#define ORANGE 4
#define WHITE 5

namespace Cube
{
	class Face
	{
	public:
		Face();

		// 2D array of face values
		// [row][index]
		int ** m_ValuesArrays;
	};
}