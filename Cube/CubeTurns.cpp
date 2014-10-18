#include "Cube.h"

namespace Rubiks
{
	void Cube::TurnTopCW()
	{
		// Save Green
		int saveTopRight = m_Faces[1].m_BottomRight;
		int saveTopMiddle = m_Faces[1].m_CenterRight;
		int saveTopLeft = m_Faces[1].m_TopRight;

		// Orange(Looking @) to Green
		m_Faces[1].m_BottomRight = m_Faces[4].m_TopRight;
		m_Faces[1].m_CenterRight = m_Faces[4].m_TopMiddle;
		m_Faces[1].m_TopRight = m_Faces[4].m_TopLeft;

		// Blue to Orange(Looking @)
		m_Faces[4].m_TopRight = m_Faces[3].m_TopLeft;
		m_Faces[4].m_TopMiddle = m_Faces[3].m_CenterLeft;
		m_Faces[4].m_TopLeft = m_Faces[3].m_BottomLeft;

		// Red to Blue
		m_Faces[3].m_BottomLeft = m_Faces[0].m_BottomRight;
		m_Faces[3].m_CenterLeft = m_Faces[0].m_BottomMiddle;
		m_Faces[3].m_TopLeft = m_Faces[0].m_BottomLeft;

		// Green to Red
		m_Faces[0].m_BottomLeft = saveTopRight;
		m_Faces[0].m_BottomMiddle = saveTopMiddle;
		m_Faces[0].m_BottomRight = saveTopLeft;
	}
}