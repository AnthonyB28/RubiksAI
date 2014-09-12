#include "Reader/Reader.h"
#include <stdio.h>

int main(int argc, const char* argv[])
{
	Reader *input = new Reader();
	
	if (input->LoadValidFile("input.txt"))
	{
		input->LogInputCube();
	}
	else
	{
		std::cout << "INVALID_INPUT\n";
		system("pause");
	}

	
}