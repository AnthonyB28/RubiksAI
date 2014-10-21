#include "Cube.h"

namespace Rubiks
{
	Cube* Cube::GetGoalCube()
	{
		Cube* goal = new Cube();
		for (int i = 0; i < 6; ++i)
		{
			for (int x = 0; x < 3; ++x)
			{
				for (int y = 0; y < 3; ++y)
				{
					goal->m_Faces[i].SetColor(x, y, i);
				}
			}
		}

		return goal;
	}
}