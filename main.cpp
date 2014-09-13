#include "Reader/Reader.h"
#include <stdio.h>

// DEBUG_MODE is my preprocessor macro in the sln file
// Define only when testing code for additional output.
// Undefined will produce professor desired output for class.

int main(int argc, const char* argv[])
{
	Reader *input = new Reader();

#ifdef DEBUG_MODE
	if (input->LoadValidFile("input.txt"))
	{

		std::cout << "VALID_INPUT\n";
		input->LogInputCube();
	}
	else
	{
		std::cout << "INVALID_INPUT\n";
	}
	system("pause");
#else
	std::cout << std::boolalpha << input->LoadValidFile("input.txt");
	system("pause");
#endif
	
}