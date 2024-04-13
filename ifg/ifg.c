//------------------------------------------------------------------------------
// ifg.cpp : Defines the entry point for the application.
//
#include <stdio.h>

int main(int argc, char** argv)
{
	int index;

	for (index = 1; index < argc; index++)
	{
		printf("Command line option #%d: '%s'\n", index, argv[index]);
	}

	return 0;
}
