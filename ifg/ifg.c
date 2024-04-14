//------------------------------------------------------------------------------
// ifg.cpp : Defines the entry point for the application.
//
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int xMin = INT_MAX;
int xMax = INT_MIN;
int yMin = INT_MAX;
int yMax = INT_MIN;
int samplingLevel = 1;
char* outputFileName = NULL;

int main(int argc, char** argv)
{
	if (!ParseCommandLine(argc, argv))
	{
		exit(-1);
	}

	return 0;
}
