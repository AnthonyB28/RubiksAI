#include "Reader.h"

Reader::Reader()
	: m_ColorCount()
	, m_Cube()
{
	for (int i = 0; i < 6; ++i)
	{
		m_ColorCount[i] = 0;
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
			if (row == RUBIKS_WIDTH)
			{
				// Special case for Carle's input
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
		}


		if (isValid)
		{
			// Check valid color face count
			for (int i = 0; i < 6; ++i)
			{
				if (m_ColorCount[i] != RUBIKS_MAXCOLORCOUNT)
				{
					isValid = false;
				}
			}

			// Are there too many rows in the input file?
			if (processedLines != RUBIKS_WIDTH * 4)
			{
				isValid = false;
			}
		}
	}
	catch (int e)
	{
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

		m_Cube[face].m_ValuesArrays[row][i] = colorToAdd;

		// Check if our color exceeds the maximum we should have!!
		++m_ColorCount[colorToAdd];
		if (m_ColorCount[colorToAdd] > RUBIKS_MAXCOLORCOUNT)
		{
			return false;
		}

		++i;

		// End of row? Stop!
		if (i == RUBIKS_WIDTH) 
		{
			break;
		}
	}

	// Valid input with size in 3 steps
	int size = values->length();
	if (size % RUBIKS_WIDTH) // If our input is not divisible by the number of cubes in a row, its invalid.
	{
		return false;
	}
	else if (size > RUBIKS_WIDTH) // Input line can be multi-faced, need to recursively build the next face.
	{
		std::string substr = values->substr(RUBIKS_WIDTH);
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
	for (int x = 0; x < RUBIKS_WIDTH; ++x)
	{
		for (int y = 0; y < RUBIKS_WIDTH; ++y)
		{
			std::cout << m_Cube[0].m_ValuesArrays[x][y];
		}

		std::cout << '\n';
	}

	for (int x = 0; x < RUBIKS_WIDTH; ++x)
	{
		for (int z = 1; z < 4; ++z)
		{
			for (int y = 0; y < RUBIKS_WIDTH; ++y)
			{
				std::cout << m_Cube[z].m_ValuesArrays[x][y];
			}
			
		}
		std::cout << '\n';
	}

	for (int z = 4; z < 6; ++z)
	{
		for (int x = 0; x < RUBIKS_WIDTH; ++x)
		{
			for (int y = 0; y < RUBIKS_WIDTH; ++y)
			{
				std::cout << m_Cube[z].m_ValuesArrays[x][y];
			}

			std::cout << '\n';
		}
	}
}