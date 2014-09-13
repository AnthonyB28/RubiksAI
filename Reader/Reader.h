#include "../Cube/Face.h"
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
	unsigned int m_ColorCount[6];
	bool m_CenterColorsMade[6];
	Cube::Face m_Cube[6];
};