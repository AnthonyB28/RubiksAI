#include "../Cube/Cube.h"
#include <fstream>
#include <string>
#include <iostream>

class Reader
{
public:
	Reader();
	bool LoadValidFile(std::string filePath);
	void LogInputCube();

private :
	bool BuildFace(int cube, int row, const std::string * const values);

	Rubiks::Cube m_Cube;

	unsigned int m_ColorCount[6]; // # of times a color is created
	unsigned int m_CornerColorCount[6];
	unsigned int m_EdgeColorCount[6];
};