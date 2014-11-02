#include "Reader/Reader.h"
#include <stdio.h>
#include <sstream>

// DEBUG_MODE is my preprocessor macro in the sln file
// Define only when testing code for additional output.
// Undefined will produce professor desired output for class.

int main(int argc, const char* argv[])
{
	bool testValidityFolder = false;
	Reader *input = new Reader();

	//Rubiks::Cube::GenerateCornerTables(12);
	std::vector<char> cornersMap(UNIQUE_CORNERS / 2+1);
	std::vector<char> edgesAMap(UNIQUE_EDGES / 2+1);
	std::vector<char> edgesBMap(UNIQUE_EDGES / 2+1);
	Rubiks::Cube::TableFileLoad("corners.bin", cornersMap);
	Rubiks::Cube::TableFileLoad("edges.bin", edgesAMap);
	Rubiks::Cube::TableFileLoad("edges2.bin", edgesBMap);
	if (argv[1] && !testValidityFolder) // Single file to test if valid Rubiks Cube
	{
#ifdef DEBUG_MODE // Only for putting debug information out. Else just print if its a valid cube.
		if (input->LoadCubeFile(argv[1], true))
		{
			std::cout << "VALID_INPUT\n";
			Rubiks::Cube cube = input->GetCube();
			cube.LogCube();
			cube.Solve(cornersMap, edgesAMap, edgesBMap);
		}
		else
		{
			std::cout << "INVALID_INPUT\n";
		}
		system("pause");
#else
		bool valid = input->LoadCubeFile(argv[1], true);
		std::cout << std::boolalpha << valid;
		Rubiks::Cube cube = input->GetCube();
		if (valid)
		{
			cube.Solve(cornersMap, edgesAMap, edgesBMap);
		}
		system("pause");
#endif
	}
	else if (testValidityFolder) // Test an entire folder for validity
	{
		int passed = 0;
		for (int i = 0; i < 16; ++i)
		{
			input = new Reader();
			std::stringstream file;
			//file << "valid\\test" << i << ".txt";
#ifdef DEBUG_MODE
			file << "scrambles\\countstates\\cube" << i ;
#else
			file << "..\\..\\scrambles\\countstates\\cube" << i ;
#endif
			if (!input->LoadCubeFile(file.str(), true))
			{
				std::cout << "Test " << i << " failed\n";
			}
			else
			{
				Rubiks::Cube cube = input->GetCube();
				++passed;
				cube.Solve(cornersMap, edgesAMap, edgesBMap);
			}
			delete input;
		}
		std::cout << "Finished all tests " << " Passed:" << passed << "\n";
		system("pause");
	}
	else
	{
		std::cout << "Please provide input file path as argument before execution\n";
		bool valid = input->LoadCubeFile("input.txt", true);
		std::cout << std::boolalpha << valid;
		if (valid)
		{
			Rubiks::Cube cube = input->GetCube();
			cube.Solve(cornersMap, edgesAMap, edgesBMap);
		}
		system("pause");
	}
}