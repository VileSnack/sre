//------------------------------------------------------------------------------
// parse.c
//
// Parses the command line.
//
#include <stdio.h>
#include <stdbool.h>
#include "funcs.h"

extern int xMin;
extern int xMax;
extern int yMin;
extern int yMax;
extern int samplingLevel;
extern char* outputFileName;

bool ParseCommandLine(int argc, char** argv)
{
	int index;

	for (index = 1; index < argc; index++)
	{
		if (0 == strcmp("-l", argv[index]))
		{
			index++;

			if (index == argc)
			{
				fprintf(stderr,
					"***** Error: A value must be supplied when setting the left column.\n"
				);

				return false;
			}

			if (sscanf(argv[index], "%d", &xMin) < 1)
			{
				fprintf(stderr,
					"***** Error: '%s' is not a valid integer value (reading -l option).\n",
					argv[index]
				);

				return false;
			}
		}
		else if (0 == strcmp("-r", argv[index]))
		{
			index++;

			if (index == argc)
			{
				fprintf(stderr,
					"***** Error: A value must be supplied when setting the right column.\n"
				);

				return false;
			}

			if (sscanf(argv[index], "%d", &xMax) < 1)
			{
				fprintf(stderr,
					"***** Error: '%s' is not a valid integer value (reading -r option).\n",
					argv[index]
				);

				return false;
			}
		}
		else if (0 == strcmp("-t", argv[index]))
		{
			index++;

			if (index == argc)
			{
				fprintf(stderr,
					"***** Error: A value must be supplied when setting the top row.\n"
				);

				return false;
			}

			if (sscanf(argv[index], "%d", &yMin) < 1)
			{
				fprintf(stderr,
					"***** Error: '%s' is not a valid integer value (reading -t option).\n",
					argv[index]
				);

				return false;
			}
		}
		else if (0 == strcmp("-b", argv[index]))
		{
			index++;

			if (index == argc)
			{
				fprintf(stderr,
					"***** Error: A value must be supplied when setting the bottom row.\n"
				);

				return false;
			}

			if (sscanf(argv[index], "%d", &yMax) < 1)
			{
				fprintf(stderr,
					"***** Error: '%s' is not a valid integer value (reading -b option).\n",
					argv[index]
				);

				return false;
			}
		}
		else if (0 == strcmp("-w", argv[index]))
		{
			index++;

			if (index == argc)
			{
				fprintf(stderr,
					"***** Error: A value must be supplied when setting the width.\n"
				);

				return false;
			}

			if (sscanf(argv[index], "%d", &xMax) < 1)
			{
				fprintf(stderr,
					"***** Error: '%s' is not a valid integer value (reading -w option).\n",
					argv[index]
				);

				return false;
			}

			xMax--;
			xMin = 0;
		}
		else if (0 == strcmp("-h", argv[index]))
		{
			index++;

			if (index == argc)
			{
				fprintf(stderr,
					"***** Error: A value must be supplied when setting the height.\n"
				);

				return false;
			}

			if (sscanf(argv[index], "%d", &yMax) < 1)
			{
				fprintf(stderr,
					"***** Error: '%s' is not a valid integer value (reading -h option).\n",
					argv[index]
				);

				return false;
			}

			yMax--;
			yMin = 0;
		}
		else if (0 == strcmp("-a", argv[index]))
		{
			index++;

			if (index == argc)
			{
				fprintf(stderr,
					"***** Error: A value must be supplied when setting the sampling level.\n"
				);

				return false;
			}

			if (sscanf(argv[index], "%d", &samplingLevel) < 1)
			{
				fprintf(stderr,
					"***** Error: '%s' is not a valid integer value (reading -a option).\n",
					argv[index]
				);

				return false;
			}
		}
		else if (0 == strcmp("-f", argv[index]))
		{
			index++;
			outputFileName = argv[index];
		}
	}

	if (xMin > xMax)
	{
		fprintf(stderr, "***** Error: Both left and right columns must be set. Use the -l and -r options, or the -w option.\n");

		return false;
	}

	if (yMin > yMax)
	{
		fprintf(stderr, "***** Error: Both top and bottom rows must be set. Use the -t and -b options, or the -h option.\n");

		return false;
	}

	if (NULL == outputFileName)
	{
		fprintf(stderr, "***** Error: An output file name must be set. Use the -f option to set the output file name.\n");

		return false;
	}

	return true;
}
