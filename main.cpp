#include "Reader/Reader.h"
#include <stdio.h>

int main(int argc, const char* argv[])
{
	Reader *input = new Reader();
	input->LoadValidFile("test.txt");
	input->LogInputCube();
}