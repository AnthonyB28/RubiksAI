#include "Reader/Reader.h"
#include <stdio.h>

int main(int argc, const char* argv[])
{
	Reader *input = new Reader();
	
	if (input->LoadValidFile("input.txt"))
	{
		std::cout << "VALID_INPUT\n";
#ifdef DEBUG_MODE
		input->LogInputCube();
#endif
	}
	else
	{
		std::cout << "INVALID_INPUT\n";
	}
	system("pause");
}