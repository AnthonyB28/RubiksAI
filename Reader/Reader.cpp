#include "Reader.h"

bool Reader::LoadValidFile(std::string filePath)
{	
	std::ifstream input(filePath);
	std::string inputLine;

	int facesDone = 0;
	int row = 0;

	while (std::getline(input,inputLine))
	{
		std::cout << inputLine << '\n';
		BuildFace(facesDone, row, &inputLine);
		++row;
		if (row == RUBIKS_WIDTH)
		{
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
	}
	input.close();
	return true;
}

void Reader::BuildFace(int cube, int row, const std::string * const values)
{
	int i = 0;
	for (const char& c : *values)
	{
		switch (c)
		{
		case 'R':
			m_Cube[cube].m_ValuesArrays[row][i] = 0;
			break;
		case 'B':
			m_Cube[cube].m_ValuesArrays[row][i] = 1;
			break;
		case 'G':
			m_Cube[cube].m_ValuesArrays[row][i] = 2;
			break;
		case 'Y':
			m_Cube[cube].m_ValuesArrays[row][i] = 3;
			break;
		case 'W':
			m_Cube[cube].m_ValuesArrays[row][i] = 4;
			break;
		case 'O':
			m_Cube[cube].m_ValuesArrays[row][i] = 5;
			break;
		}
		++i;
		if (i == RUBIKS_WIDTH)
		{
			break;
		}
	}
	if (values->length() > 3)
	{
		std::string substr = values->substr(3);
		BuildFace(cube + 1, row, &substr);
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
	system("pause");
}