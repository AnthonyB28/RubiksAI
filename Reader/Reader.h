#include "../Cube/Cube.h"
#include <fstream>
#include <string>
#include <iostream>

class Reader
{
public:
	Reader();

	bool LoadCubeFile(std::string const & filePath, bool const checkValid);
	Rubiks::Cube GetCube() const;

private :
	bool BuildFace(int const cube, int const row, std::string const * const values);

	bool m_CheckValid;
	unsigned int m_ColorCount[6]; // # of times a color is created
	unsigned int m_CornerColorCount[6];
	unsigned int m_EdgeColorCount[6];

	Rubiks::Cube m_Cube;
};