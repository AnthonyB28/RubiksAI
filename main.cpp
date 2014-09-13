#include "Reader/Reader.h"
#include <stdio.h>

// DEBUG_MODE is my preprocessor macro in the sln file
// Define only when testing code for additional output.
// Undefined will produce professor desired output for class.

int main(int argc, const char* argv[])
{
	Reader *input = new Reader();
	
	if (input->LoadValidFile("input.txt"))
	{
#ifdef DEBUG_MODE
		std::cout << "VALID_INPUT\n";
		input->LogInputCube();
#else
		std::cout << "true";
#endif
	}
	else
	{
#ifdef DEBUG_MODE
		std::cout << "INVALID_INPUT\n";
#else
		std::cout << "false";
#endif
	}
	system("pause");
}