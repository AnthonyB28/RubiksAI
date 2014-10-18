#include "../Cube/Cube.h"
#include <fstream>
#include <string>
#include <iostream>

class Reader
{
public:
	Reader();
	bool LoadCubeFile(std::string filePath, bool checkValid);
	void LogCube();

	Rubiks::Cube m_Cube;

private :
	bool BuildFace(int cube, int row, const std::string * const values);

	bool m_CheckValid;
	unsigned int m_ColorCount[6]; // # of times a color is created
	unsigned int m_CornerColorCount[6];
	unsigned int m_EdgeColorCount[6];
};