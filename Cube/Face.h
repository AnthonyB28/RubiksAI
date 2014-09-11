#define RUBIKS_WIDTH 3
#define RUBIKS_KEY "RED 0 BLUE 1 GREEN 2 YELLOW 3 WHITE 4 ORANGE 5"

namespace Cube
{
	class Face
	{
	public:
		Face();
		int ** m_ValuesArrays;
	};
}