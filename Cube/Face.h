#define RUBIKS_WIDTH 3 // This won't work with anything other than 3x3 I think
#define RUBIKS_KEY "RED 0 GREEN 1 YELLOW 2 BLUE 3 ORANGE 4 WHITE 5 "
#define RED 0
#define GREEN 1
#define YELLOW 2
#define BLUE 3
#define ORANGE 4
#define WHITE 5

namespace Cube
{
	static const int MAX_COLOR_COUNT = RUBIKS_WIDTH*RUBIKS_WIDTH;

	class Face
	{
	public:
		Face();

		int ** m_ValuesArrays; // 2D array of face values [row][index]
		static const int CENTER = static_cast<int>((RUBIKS_WIDTH / 2.0) + 0.5 - 1);
	};
}