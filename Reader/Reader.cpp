#include "Reader.h"

Reader::Reader()
	: m_Cube()
{
	// Init color trackers
	for (int i = 0; i < 6; ++i)
	{
		m_ColorCount[i] = 0;
		m_CornerColorCount[i] = 0;
		m_EdgeColorCount[i] = 0;
		//m_CenterColorsMade[i] = false;
	}
}

bool Reader::LoadValidFile(std::string filePath)
{	
	std::ifstream input(filePath);
	std::string inputLine;

	bool isValid = true;
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
			if (!BuildFace(facesDone, row, &inputLine))
			{
				isValid = false;
				break;
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


		if (isValid)
		{
			// Check valid color count
			// Check is done earlier too, but just to be sure!
			for (int i = 0; i < 6; ++i)
			{
				if (m_ColorCount[i] != 9)
				{
					isValid = false;
					break;
				}
			}

			// Check corner and edges color count
			for (int i = 0; i < 6; ++i)
			{
				if (m_CornerColorCount[i] != 4 || m_EdgeColorCount[i] != 4)
				{
					isValid = false;
					break;
				}
			}


			// Check valid corners
			//isValid = m_Cube.CheckValidCorners();

			// Are there too many rows in the input file?
			if (processedLines != 12)
			{
				isValid = false;
			}
		}
	}
	catch (int e)
	{
		e = 0;
		isValid = false; // If we somehow encounter a parse issue, input is invalid!
	}

	input.close();
	return isValid;
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

			/*  THE ABOVE CHECK ELIMINATES THIS, BUT STILL NICE TO HAVE!
				// Check that we don't have multiple center cubes of same color!
				if (m_CenterColorsMade[colorToAdd])
				{
					return false;
				}
				else
				{
					m_CenterColorsMade[colorToAdd] = true;
				}
			*/
		}
		
		// Check if our color exceed 9
		++m_ColorCount[colorToAdd];
		if (m_ColorCount[colorToAdd] > 9)
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
			(row == 1 && i == 1) ||
			(row == 1 && i == 2) ||
			(row == 2 && i == 1))
		{
			++m_EdgeColorCount[colorToAdd];
		}

		
		m_Cube.m_Faces[face].m_ValuesArrays[row][i] = colorToAdd;

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

void Reader::LogInputCube()
{
	std::cout << "----------\n";
	std::cout << RUBIKS_KEY << '\n';
	for (int x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 3; ++y)
		{
			std::cout << m_Cube.m_Faces[0].m_ValuesArrays[x][y];
		}

		std::cout << '\n';
	}

	for (int x = 0; x < 3; ++x)
	{
		for (int z = 1; z < 4; ++z)
		{
			for (int y = 0; y < 3; ++y)
			{
				std::cout << m_Cube.m_Faces[z].m_ValuesArrays[x][y];
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
				std::cout << m_Cube.m_Faces[z].m_ValuesArrays[x][y];
			}

			std::cout << '\n';
		}
	}
}