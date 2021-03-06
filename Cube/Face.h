#define RUBIKS_KEY "RED 0 GREEN 1 YELLOW 2 BLUE 3 ORANGE 4 WHITE 5 "
#define RED 0
#define GREEN 1
#define YELLOW 2
#define BLUE 3
#define ORANGE 4
#define WHITE 5

#include "Cubies.h"

namespace Rubiks
{
	class Face
	{
	public:
		Face();
		CornerCubies GetCorners() const; // Gets the array of corner values
		EdgeCubies GetEdges() const; // Gets the array of edge values
		
		void SetColor(int const row, int const column, int const val);
		unsigned int GetColor(int const row, int const column) const;

		// three-bit unsigned field,
		// allowed values are 0...7
		unsigned int m_TopLeft : 3;
		unsigned int m_TopMiddle : 3;
		unsigned int m_TopRight : 3;
		unsigned int m_CenterLeft : 3;
		unsigned int m_CenterMiddle : 3;
		unsigned int m_CenterRight : 3;
		unsigned int m_BottomLeft : 3;
		unsigned int m_BottomMiddle : 3;
		unsigned int m_BottomRight : 3;
	};
}