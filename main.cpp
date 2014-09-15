#include "Reader/Reader.h"
#include <stdio.h>
#include <boost/timer.hpp>

// DEBUG_MODE is my preprocessor macro in the sln file
// Define only when testing code for additional output.
// Undefined will produce professor desired output for class.

int main(int argc, const char* argv[])
{
	boost::timer t;
	Reader *input = new Reader();

	if (argv[1])
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
	else
	{
		std::cout << "Please provide input file path as argument before execution\n";
		system("pause");
	}
}