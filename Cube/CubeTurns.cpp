#include "Cube.h"
#include <iostream>
namespace Rubiks
{

	void Cube::LogCube() const
	{
		std::cout << "----------\n";
		std::cout << RUBIKS_KEY << '\n';
		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				std::cout << m_Faces[0].GetColor(x, y);
			}

			std::cout << '\n';
		}

		for (int x = 0; x < 3; ++x)
		{
			for (int z = 1; z < 4; ++z)
			{
				for (int y = 0; y < 3; ++y)
				{
					std::cout << m_Faces[z].GetColor(x, y);
				}

			}
			std::cout << '\n';
		}

		for (int z = 4; z < 6; ++z)
		{
			for (int x = 0; x < 3; ++x)
			{
				for (int y = 0; y < 3; ++y)
				{
					std::cout << m_Faces[z].GetColor(x, y);
				}

				std::cout << '\n';
			}
		}
	}

	void Cube::TurnTopCW() // Note this is turning left
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

	void Cube::TurnTopACW()
	{
		for (int i = 0; i < 3; ++i)
		{
			TurnTopCW();
		}
	}

	void Cube::TurnBottomCW() // Note this is turning right
	{
		// Save Green
		int saveBottomRight = m_Faces[1].m_TopLeft;
		int saveBottomMiddle = m_Faces[1].m_CenterLeft;
		int saveBottomLeft = m_Faces[1].m_BottomLeft;

		// Red to Green
		m_Faces[1].m_TopLeft = m_Faces[0].m_TopRight;
		m_Faces[1].m_CenterLeft = m_Faces[0].m_TopMiddle;
		m_Faces[1].m_BottomLeft = m_Faces[0].m_TopLeft;

		// Blue to Red
		m_Faces[0].m_TopLeft = m_Faces[3].m_TopRight;
		m_Faces[0].m_TopMiddle = m_Faces[3].m_CenterRight;
		m_Faces[0].m_TopRight = m_Faces[3].m_BottomRight;

		// Orange(Looking @) to Blue
		m_Faces[3].m_TopRight = m_Faces[4].m_BottomRight;
		m_Faces[3].m_CenterRight = m_Faces[4].m_BottomMiddle;
		m_Faces[3].m_BottomRight= m_Faces[4].m_BottomLeft;

		// Green to Orange
		m_Faces[4].m_BottomRight = saveBottomLeft;
		m_Faces[4].m_BottomMiddle = saveBottomMiddle;
		m_Faces[4].m_BottomLeft = saveBottomRight;

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

	void Cube::TurnBottomACW()
	{
		for (int i = 0; i < 3; ++i)
		{
			TurnBottomCW();
		}
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

	void Cube::TurnRightACW()
	{
		for (int i = 0; i < 3; ++i)
		{
			TurnRightCW();
		}
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

	void Cube::TurnLeftACW()
	{
		for (int i = 0; i < 3; ++i)
		{
			TurnLeftCW();
		}
	}

	void Cube::TurnFrontCW() // Note this is turning right
	{
		// Save Blue
		int saveLeft = m_Faces[3].m_BottomLeft;
		int saveMiddle = m_Faces[3].m_BottomMiddle;
		int saveRight = m_Faces[3].m_BottomRight;

		// Yellow to Blue
		m_Faces[3].m_BottomLeft = m_Faces[2].m_BottomLeft;
		m_Faces[3].m_BottomMiddle = m_Faces[2].m_BottomMiddle;
		m_Faces[3].m_BottomRight = m_Faces[2].m_BottomRight;

		// Green to Yellow
		m_Faces[2].m_BottomLeft = m_Faces[1].m_BottomLeft;
		m_Faces[2].m_BottomMiddle = m_Faces[1].m_BottomMiddle;
		m_Faces[2].m_BottomRight = m_Faces[1].m_BottomRight;

		// White to Green
		m_Faces[1].m_BottomRight = m_Faces[5].m_TopLeft;
		m_Faces[1].m_BottomMiddle = m_Faces[5].m_TopMiddle;
		m_Faces[1].m_BottomLeft = m_Faces[5].m_TopRight;

		// Blue to White
		m_Faces[5].m_TopRight = saveLeft;
		m_Faces[5].m_TopMiddle = saveMiddle;
		m_Faces[5].m_TopLeft = saveRight;
		
		// Rotate Orange
		saveLeft = m_Faces[4].m_TopLeft;
		saveMiddle = m_Faces[4].m_TopMiddle;
		saveRight = m_Faces[4].m_TopRight;

		m_Faces[4].m_TopLeft = m_Faces[4].m_BottomLeft;
		m_Faces[4].m_TopMiddle = m_Faces[4].m_CenterLeft;
		m_Faces[4].m_BottomLeft = m_Faces[4].m_BottomRight;
		m_Faces[4].m_CenterLeft = m_Faces[4].m_BottomMiddle;
		m_Faces[4].m_BottomMiddle = m_Faces[4].m_CenterRight;
		m_Faces[4].m_BottomRight = saveRight;
		m_Faces[4].m_TopRight = saveLeft;
		m_Faces[4].m_CenterRight = saveMiddle;
	}

	void Cube::TurnFrontACW()
	{
		for (int i = 0; i < 3; ++i)
		{
			TurnFrontCW();
		}
	}

	void Cube::TurnBackCW() // Note this is turning left
	{
		// Save Yellow
		int saveLeft = m_Faces[2].m_TopLeft;
		int saveMiddle = m_Faces[2].m_TopMiddle;
		int saveRight = m_Faces[2].m_TopRight;

		// Blue to Yellow
		m_Faces[2].m_TopLeft = m_Faces[3].m_TopLeft;
		m_Faces[2].m_TopMiddle = m_Faces[3].m_TopMiddle;
		m_Faces[2].m_TopRight = m_Faces[3].m_TopRight;

		// White to Blue
		m_Faces[3].m_TopRight = m_Faces[5].m_BottomLeft;
		m_Faces[3].m_TopMiddle = m_Faces[5].m_BottomMiddle;
		m_Faces[3].m_TopLeft = m_Faces[5].m_BottomRight;

		// Green to White
		m_Faces[5].m_BottomRight = m_Faces[1].m_TopLeft;
		m_Faces[5].m_BottomMiddle = m_Faces[1].m_TopMiddle;
		m_Faces[5].m_BottomLeft = m_Faces[1].m_TopRight;

		// Yellow to Green
		m_Faces[1].m_TopLeft = saveLeft;
		m_Faces[1].m_TopMiddle = saveMiddle;
		m_Faces[1].m_TopRight = saveRight;

		// Rotate Orange
		saveLeft = m_Faces[0].m_TopLeft;
		saveMiddle = m_Faces[0].m_TopMiddle;
		saveRight = m_Faces[0].m_TopRight;

		m_Faces[0].m_TopLeft = m_Faces[0].m_BottomLeft;
		m_Faces[0].m_TopMiddle = m_Faces[0].m_CenterLeft;
		m_Faces[0].m_BottomLeft = m_Faces[0].m_BottomRight;
		m_Faces[0].m_CenterLeft = m_Faces[0].m_BottomMiddle;
		m_Faces[0].m_BottomMiddle = m_Faces[0].m_CenterRight;
		m_Faces[0].m_BottomRight = saveRight;
		m_Faces[0].m_TopRight = saveLeft;
		m_Faces[0].m_CenterRight = saveMiddle;
	}

	void Cube::TurnBackACW()
	{
		for (int i = 0; i < 3; ++i)
		{
			TurnBackCW();
		}
	}


}