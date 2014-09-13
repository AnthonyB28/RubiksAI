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

	Cube::Face m_Cube[6]; // Rubik's Cube representation - note for assignment each index happens to represent face color!

	unsigned int m_ColorCount[6]; // # of times a color is created
	//bool m_CenterColorsMade[6]; // has center color been created yet?
};