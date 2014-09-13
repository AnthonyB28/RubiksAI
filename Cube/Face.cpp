#include "Face.h"

namespace Cube
{
	Face::Face()
		: m_ValuesArrays()
	{
		m_ValuesArrays = new int*[RUBIKS_WIDTH];
		for (int init = 0; init < RUBIKS_WIDTH; ++init)
		{
			m_ValuesArrays[init] = new int[RUBIKS_WIDTH];
		}
	}

	// Gets the Face center color
	// NOTE not sure this applies to 2x2 or 4x4?
	int Face::GetCenterColor()
	{
		return m_ValuesArrays[1][Cube::MAX_COLOR_COUNT];
	}
}