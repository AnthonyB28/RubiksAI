#define RUBIKS_WIDTH 3

namespace Cube
{
	class Face
	{
	public:
		Face(int ** faceValues);
		int ** m_ValuesArrays;
	};
}