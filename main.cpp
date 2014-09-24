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

	if (argv[1] && !test)
	{
#ifdef DEBUG_MODE
		if (input->LoadValidFile(argv[1]))
		{
			std::cout << "VALID_INPUT\n";
			input->LogInputCube();
		}
		else
		{
			std::cout << "INVALID_INPUT\n";
		}
		std::cout << t.elapsed();
		system("pause");
#else
		std::cout << std::boolalpha << input->LoadValidFile(argv[1]);
		system("pause");
#endif
	}
	else if (test)
	{
		int passed = 0;
		for (int i = 1; i < 10; ++i)
		{
			input = new Reader();
			std::stringstream file;
			file << "invalid\\test" << i << ".txt";
			if (!input->LoadValidFile(file.str()))
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