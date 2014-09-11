#include "../Cube/Face.h"
#include <fstream>
#include <string>
#include <iostream>

class Reader
{
public:
	bool LoadValidFile(std::string filePath);
	void LogInputCube();

private :

	void BuildFace(int cube, int row, const std::string * const values);
	Cube::Face m_Cube[6];
};