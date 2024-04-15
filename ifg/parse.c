//------------------------------------------------------------------------------
// parse.c
//
// Parses the command line.
//
#include <limits.h>
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
		if ('-' != argv[index][0])
		{
			fprintf(stderr,
				"***** Error: '%s' is not a valid option.\n",
				argv[index]
			);

			return false;
		}

		switch (argv[index][1])
		{
			case 'l':
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
			break;

			case 'r':
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
			break;

			case 't':
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
			break;

			case 'b':
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
			break;

			case 'w':
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
			break;

			case 'h':
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
			break;

			case 'a':
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
			break;

			case 'f':
				index++;
				outputFileName = argv[index];
			break;

			case 'i':
				// dummy case because this is valid but not processed here.
			break;

			default:
				fprintf(stderr,
					"***** Error: '%s' is not a valid option.\n",
					argv[index]
				);

				return false;
			break;
		}
	}

	if (xMin == INT_MAX)
	{
		fprintf(stderr, "***** Error: Left column must be set. Use the -l or -w option.\n");

		return false;
	}

	if (xMax == INT_MIN)
	{
		fprintf(stderr, "***** Error: Right column must be set. Use the -r or -w option.\n");

		return false;
	}

	if (yMin == INT_MAX)
	{
		fprintf(stderr, "***** Error: Top row must be set. Use the -t or -h option.\n");

		return false;
	}

	if (yMax == INT_MIN)
	{
		fprintf(stderr, "***** Error: Bottom row must be set. Use the -b or -h option.\n");

		return false;
	}

	if (NULL == outputFileName)
	{
		fprintf(stderr, "***** Error: An output file name must be set. Use the -f option.\n");

		return false;
	}

	return true;
}
