#include "Reader/Reader.h"
#include <stdio.h>
#include <sstream>

// DEBUG_MODE is my preprocessor macro in the sln file
// Define only when testing code for additional output.
// Undefined will produce professor desired output for class.

int main(int argc, const char* argv[])
{
	bool test = false;
	Reader *input = new Reader();

	//Rubiks::Cube::IASearch(12);
	if (argv[1] && !test)
	{
#ifdef DEBUG_MODE
		if (input->LoadCubeFile(argv[1], false))
		{
			std::cout << "VALID_INPUT\n";
			input->LogCube();
			input->m_Cube.TurnBackCW();
			input->LogCube();
		}
		else
		{
			std::cout << "INVALID_INPUT\n";
		}
		system("pause");
#else
		std::cout << std::boolalpha << input->LoadCubeFile(argv[1], false);
		system("pause");
#endif
	}
	else if (test)
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
			}
			delete input;
		}
		std::cout << "Finished all tests " << " Passed:" << passed << "\n";
		system("pause");
	}
	else
	{
		std::cout << "Please provide input file path as argument before execution\n";
		system("pause");
	}
}