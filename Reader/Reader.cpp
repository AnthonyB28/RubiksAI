#include "Reader.h"

Reader::Reader()
	: m_Cube()
	, m_CheckValid(true)
{
	// Init color trackers
	for (int i = 0; i < 6; ++i)
	{
		m_ColorCount[i] = 0;
		m_CornerColorCount[i] = 0;
		m_EdgeColorCount[i] = 0;
	}
}

bool Reader::LoadCubeFile(std::string filePath, bool checkValid)
{
	m_CheckValid = checkValid;
	std::ifstream input(filePath.c_str());
	std::string inputLine;
	int facesDone = 0;
	int row = 0;
	try
	{
		int processedLines = 0; // Should have RUBIKS_WIDTH * 4 lines of input

		// Parse input by lines = rows of a cube(s) face(s)
		while (std::getline(input, inputLine))
		{
#ifdef DEBUG_MODE
			std::cout << inputLine << '\n';
#endif
			std::size_t end = inputLine.find_last_not_of('\r');
			std::size_t beginning = inputLine.find_first_not_of('\r');
			std::string inputTrim = inputLine.substr(beginning, end - beginning + 1);
			if (!BuildFace(facesDone, row, &inputTrim))
			{
				input.close();
				return false;
			}
			++row;
			if (row == 3)
			{
				// Special case for professor input
				// Second cube face will have 2 more faces like a + horizontally to its right
				if (facesDone == 1)
				{
					facesDone = 4;
				}
				else
				{
					++facesDone;
				}
				row = 0;
			}
			++processedLines;
			if (processedLines == 12)
			{
				break;
			}
		}

		if (m_CheckValid)
		{
			// Are there too many rows in the input file?
			if (processedLines != 12)
			{
				input.close();
				return false;
			}

			// Check valid color count
			// Check is done earlier too, but just to be sure!
			for (int i = 0; i < 6; ++i)
			{
				if (m_ColorCount[i] != 9)
				{
					input.close();
					return false;
				}
			}

			// Check corner and edges color count
			for (int i = 0; i < 6; ++i)
			{
				if (m_CornerColorCount[i] != 4 || m_EdgeColorCount[i] != 4)
				{
					input.close();
					return false;
				}
			}

			// Do our parity tests
			if (!m_Cube.CheckValidParity())
			{
				input.close();
				return false;
			}
		}
	}
	catch (int e)
	{
		e = 0;
		return false;
	}

	input.close();
	return true;
}

// Builds upon a face of a cube given a row number and the string line of input color 
// upper face (0) - second row (2) - 'RGR'
// returns if the input is a valid for our rubiks cube
bool Reader::BuildFace(int face, int row, const std::string * const values)
{
	int i = 0;
	int colorToAdd = 0;
	for (const char& c : *values)
	{
		switch (c)
		{
		case 'R':
			colorToAdd = RED;
			break;
		case 'B':
			colorToAdd = BLUE;
			break;
		case 'G':
			colorToAdd = GREEN;
			break;
		case 'Y':
			colorToAdd = YELLOW;
			break;
		case 'W':
			colorToAdd = WHITE;
			break;
		case 'O':
			colorToAdd = ORANGE;
			break;
		default :
			return false;
			break;
		}

		// Center cube of a face
		if (i == 1 && row == 1)
		{
			/* 
				Professor specific input check
				Color of face goes IN ORDER
				EG the face # happens to represent the color by order of appearence
				R is always 0, G is always 1
			*/
			if (colorToAdd != face)
			{
				return false;
			}
		}
		
		// Check if our color exceed 9
		++m_ColorCount[colorToAdd];
		if (m_ColorCount[colorToAdd] > 9 && m_CheckValid)
		{
			return false;
		}

		// Check the corner & edge colors don't exceed 4 times
		if (
			(row == 0 && i == 0) ||
			(row == 0 && i == 2) ||
			(row == 2 && i == 0) ||
			(row == 2 && i == 2))
		{
			++m_CornerColorCount[colorToAdd];
		}
		else if (
			(row == 0 && i == 1) ||
			(row == 1 && i == 0) ||
			(row == 1 && i == 2) ||
			(row == 2 && i == 1))
		{
			++m_EdgeColorCount[colorToAdd];
		}

		
		m_Cube.m_Faces[face].SetColor(row, i, colorToAdd);

		++i;

		// End of row? Stop!
		if (i == 3) 
		{
			break;
		}
	}

	// Valid input with size in 3 steps
	int size = values->length();
	if (size % 3) // If our input is not divisible by the number of cubes in a row, its invalid.
	{
		return false;
	}
	else if (size > 3) // Input line can be multi-faced, need to recursively build the next face.
	{
		std::string substr = values->substr(3);
		return BuildFace(face + 1, row, &substr);
	}
	else // Otherwise we should be valid
	{
		return true;
	}
}