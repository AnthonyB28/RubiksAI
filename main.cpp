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

	std::vector<char> cornersMap(88179841 / 2);
	std::vector<char> edgesAMap(42577921 / 2);
	std::vector<char> edgesBMap(42577921 / 2);
	Rubiks::Cube::TableFileLoad("corners.bin", cornersMap);
	Rubiks::Cube::TableFileLoad("edges.bin", edgesAMap);
	Rubiks::Cube::TableFileLoad("edges2.bin", edgesBMap);
	if (argv[1] && !testValidityFolder) // Single file to test if valid Rubiks Cube
	{
#ifdef DEBUG_MODE // Only for putting debug information out. Else just print if its a valid cube.
		if (input->LoadCubeFile(argv[1], true))
		{
			std::cout << "VALID_INPUT\n";
			input->m_Cube.LogCube();
			input->m_Cube.Solve(cornersMap, edgesAMap, edgesBMap);
		}
		else
		{
			std::cout << "INVALID_INPUT\n";
		}
		system("pause");
#else
		bool valid = input->LoadCubeFile(argv[1], true);
		std::cout << std::boolalpha << valid;
		if (valid)
		{
			input->m_Cube.Solve(cornersMap, edgesAMap, edgesBMap);
		}
		system("pause");
#endif
	}
	else if (testValidityFolder) // Test an entire folder for validity
	{
		int passed = 0;
		for (int i = 0; i < 2000; ++i)
		{
			input = new Reader();
			std::stringstream file;
			file << "valid\\test" << i << ".txt";
			if (!input->LoadCubeFile(file.str(), true))
			{
				std::cout << "Test " << i << " failed\n";
			}
			else
			{
				++passed;
				input->m_Cube.Solve(cornersMap, edgesAMap, edgesBMap);
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
			input->m_Cube.Solve(cornersMap, edgesAMap, edgesBMap);
		}
		system("pause");
	}
}