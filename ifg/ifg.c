//------------------------------------------------------------------------------
// ifg.cpp : Defines the entry point for the application.
//
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include "Pixel.h"

int xMin = INT_MAX;
int xMax = INT_MIN;
int yMin = INT_MAX;
int yMax = INT_MIN;
int samplingLevel = 1;
char* outputFileName = NULL;

const char* FILE_PATT = "%s/row%d.txt";

#define ROWFILE_NAME_BUFFER_LENGTH 20

FILE* file;

int main(int argc, char** argv)
{
	char fileName[ROWFILE_NAME_BUFFER_LENGTH];
	int index;
	int row;

	if (!ParseCommandLine(argc, argv))
	{
		exit(-1);
	}

	SetUpPixels();

	for (row = yMin; row <= yMax; row++)
	{
		for (index = 1; index < argc; index++)
		{
			if (0 != strcmp("-i", argv[index])) continue;

			index++;

			sprintf_s(fileName, ROWFILE_NAME_BUFFER_LENGTH - 1, FILE_PATT, argv[index], row);

			file = fopen(fileName, "r");

			ProcessImageFragmentFile(file);
		}

		OutputRow();
	}

	FreePixels();

	return 0;
}
