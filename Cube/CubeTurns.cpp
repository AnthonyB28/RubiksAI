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

		// Rotate yellow around
		saveTopLeft = m_Faces[2].m_TopLeft;
		saveTopMiddle = m_Faces[2].m_TopMiddle;
		saveTopRight = m_Faces[2].m_TopRight;
		m_Faces[2].m_TopLeft = m_Faces[2].m_BottomLeft;
		m_Faces[2].m_TopMiddle = m_Faces[2].m_CenterLeft;
		m_Faces[2].m_TopRight = saveTopLeft;
		m_Faces[2].m_CenterLeft = m_Faces[2].m_BottomMiddle;
		m_Faces[2].m_BottomLeft = m_Faces[2].m_BottomRight;
		m_Faces[2].m_BottomMiddle = m_Faces[2].m_CenterRight;
		m_Faces[2].m_BottomRight = saveTopRight;
		m_Faces[2].m_CenterRight = saveTopMiddle;
	}

	void Cube::TurnBottomCW()
	{
		// Save Green
		int saveBottomRight = m_Faces[1].m_TopLeft;
		int saveBottomMiddle = m_Faces[1].m_CenterLeft;
		int saveBottomLeft = m_Faces[1].m_BottomLeft;

		// Orange(Looking @) to Green
		m_Faces[1].m_BottomLeft = m_Faces[4].m_BottomRight;
		m_Faces[1].m_CenterLeft = m_Faces[4].m_BottomMiddle;
		m_Faces[1].m_TopLeft = m_Faces[4].m_BottomLeft;

		// Blue to Orange(Looking @)
		m_Faces[4].m_BottomLeft = m_Faces[3].m_BottomRight;
		m_Faces[4].m_BottomMiddle = m_Faces[3].m_CenterRight;
		m_Faces[4].m_BottomRight = m_Faces[3].m_TopRight;

		// Red to Blue
		m_Faces[3].m_TopRight = m_Faces[0].m_TopLeft;
		m_Faces[3].m_CenterRight = m_Faces[0].m_TopMiddle;
		m_Faces[3].m_BottomRight = m_Faces[0].m_TopRight;

		// Green to Red
		m_Faces[0].m_TopLeft = saveBottomLeft;
		m_Faces[0].m_TopMiddle = saveBottomMiddle;
		m_Faces[0].m_TopRight = saveBottomRight;

		// Rotate white around
		saveBottomLeft = m_Faces[5].m_TopLeft;
		saveBottomMiddle = m_Faces[5].m_TopMiddle;
		saveBottomRight = m_Faces[5].m_TopRight;
		m_Faces[5].m_TopLeft = m_Faces[5].m_BottomLeft;
		m_Faces[5].m_TopMiddle = m_Faces[5].m_CenterLeft;
		m_Faces[5].m_TopRight = saveBottomLeft;
		m_Faces[5].m_CenterLeft = m_Faces[5].m_BottomMiddle;
		m_Faces[5].m_BottomLeft = m_Faces[5].m_BottomRight;
		m_Faces[5].m_BottomMiddle = m_Faces[5].m_CenterRight;
		m_Faces[5].m_BottomRight = saveBottomRight;
		m_Faces[5].m_CenterRight = saveBottomMiddle;
	}

	void Cube::TurnRightCW() // Note this is an up turn
	{
		// Save Red
		int saveTop = m_Faces[0].m_TopRight;
		int saveMiddle = m_Faces[0].m_CenterRight;
		int saveBottom = m_Faces[0].m_BottomRight;

		// Yellow to Red
		m_Faces[0].m_TopRight = m_Faces[2].m_TopRight;
		m_Faces[0].m_CenterRight = m_Faces[2].m_CenterRight;
		m_Faces[0].m_BottomRight = m_Faces[2].m_BottomRight;

		//  Orange(Looking @ ) to Yellow
		m_Faces[2].m_TopRight = m_Faces[4].m_TopRight;
		m_Faces[2].m_CenterRight = m_Faces[4].m_CenterRight;
		m_Faces[2].m_BottomRight = m_Faces[4].m_BottomRight;

		// White to Orange
		m_Faces[4].m_TopRight = m_Faces[5].m_TopRight;
		m_Faces[4].m_CenterRight = m_Faces[5].m_CenterRight;
		m_Faces[4].m_BottomRight = m_Faces[5].m_BottomRight;

		// Red to White
		m_Faces[5].m_TopRight = saveTop;
		m_Faces[5].m_CenterRight = saveMiddle;
		m_Faces[5].m_BottomRight = saveBottom;

		// Rotate Blue around
		saveTop = m_Faces[3].m_TopLeft;
		saveMiddle = m_Faces[3].m_TopMiddle;
		saveBottom = m_Faces[3].m_TopRight;
		m_Faces[3].m_TopLeft = m_Faces[3].m_BottomLeft;
		m_Faces[3].m_TopMiddle = m_Faces[3].m_CenterLeft;
		m_Faces[3].m_TopRight = saveTop;
		m_Faces[3].m_CenterLeft = m_Faces[3].m_BottomMiddle;
		m_Faces[3].m_BottomLeft = m_Faces[3].m_BottomRight;
		m_Faces[3].m_BottomMiddle = m_Faces[3].m_CenterRight;
		m_Faces[3].m_BottomRight = saveBottom;
		m_Faces[3].m_CenterRight = saveMiddle;
	}

	void Cube::TurnLeftCW() // Note this is a down turn
	{
		// Save White
		int saveTop = m_Faces[5].m_TopLeft;
		int saveMiddle = m_Faces[5].m_CenterLeft;
		int saveBottom = m_Faces[5].m_BottomLeft;

		//  Orange(Looking @ ) to White
		m_Faces[5].m_TopLeft = m_Faces[4].m_TopLeft;
		m_Faces[5].m_CenterLeft = m_Faces[4].m_CenterLeft;
		m_Faces[5].m_BottomLeft = m_Faces[4].m_BottomLeft;

		// Yellow to Orange
		m_Faces[4].m_TopLeft = m_Faces[2].m_TopLeft;
		m_Faces[4].m_CenterLeft = m_Faces[2].m_CenterLeft;
		m_Faces[4].m_BottomLeft = m_Faces[2].m_BottomLeft;

		// Red to Yellow
		m_Faces[2].m_TopLeft = m_Faces[0].m_TopLeft;
		m_Faces[2].m_CenterLeft = m_Faces[0].m_CenterLeft;
		m_Faces[2].m_BottomLeft = m_Faces[0].m_BottomLeft;

		// White to Red
		m_Faces[0].m_TopLeft = saveTop;
		m_Faces[0].m_CenterLeft = saveMiddle;
		m_Faces[0].m_BottomLeft = saveBottom;

		// Rotate Green around
		saveTop = m_Faces[1].m_TopLeft;
		saveMiddle = m_Faces[1].m_TopMiddle;
		saveBottom = m_Faces[1].m_TopRight;
		m_Faces[1].m_TopLeft = m_Faces[1].m_BottomLeft;
		m_Faces[1].m_TopMiddle = m_Faces[1].m_CenterLeft;
		m_Faces[1].m_TopRight = saveTop;
		m_Faces[1].m_CenterLeft = m_Faces[1].m_BottomMiddle;
		m_Faces[1].m_BottomLeft = m_Faces[1].m_BottomRight;
		m_Faces[1].m_BottomMiddle = m_Faces[1].m_CenterRight;
		m_Faces[1].m_BottomRight = saveBottom;
		m_Faces[1].m_CenterRight = saveMiddle;
	}
}