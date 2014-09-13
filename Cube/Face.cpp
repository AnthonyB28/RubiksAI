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
}