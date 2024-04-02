//------------------------------------------------------------------------------
// ifc.c
// 
// Implements the 'main' function.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "Buffer.h"

const char* FILE_PATT = "row%d.txt";

#define ROWFILE_NAME_BUFFER_LENGTH 20

int main(int argc, char** argv)
{
	FILE* rowFile = NULL;
	struct Buffer buffer;
	int lastRow = -1;
	int err = 0;

	// If we ever need to, have a look at the command-line arguments here.
	if (0 < argc)
	{
		err = _chdir(argv[1]);

		if (0 != err)
		{
			switch (errno)
			{
				case 2:	// the selected directory does not exist.
					if (0 == _mkdir(argv[1]))
					{
						err = _chdir(argv[1]);
					}
					else
					{
						fprintf(stderr
							, "***** Error: Directory '%s' does not exist, creation attempt returned error code %d.\n"
							, argv[1]
							, errno
						);
						exit(-1);
					}
				break;
				default:
					fprintf(stderr
						, "***** Error: Change directory attempt returned %d.\n"
						, errno
					);
					exit(-1);
				break;
			}
		}
	}

	InitBuffer(&buffer);

	do
	{
		int column;
		int row;
		char prevChar = ' ';	// for identifying runs of white space.

		while (true)
		{
			int c = getc(stdin);

			//------------------------------------------------------------------
			// We're completely done if we hit the end-of-file.
			//
			if (EOF == c) break;

			//------------------------------------------------------------------
			// Image fragments end with a semicolon.
			//
			if (';' == c) break;

			//------------------------------------------------------------------
			// Normalize all non-printing characters to spaces.
			//
			if (c < ' ') c = ' ';

			//------------------------------------------------------------------
			// Collapse all runs of white space to a single space, and skips
			// leading white space.
			//
			if ((c == (int)' ') && (prevChar == ' ')) continue;

			//------------------------------------------------------------------
			// Remember this character for the white space collapsing on the
			// next iteration of this loop.
			//
			prevChar = (char)c;

			AppendCharToBuffer(&buffer, (char)c);
		}

		//----------------------------------------------------------------------
		// If nothing was parsed, we're done.
		//
		if (IsBufferEmpty(&buffer))
		{
			printf("No more fragments.\n");
			break;
		}

		//------------------------------------------------------------------
		// In case there was trailing white space...
		//
		TrimTail(&buffer);

		//----------------------------------------------------------------------
		// Properly terminate this image fragment (in case the files we generate
		// have other image fragment files appended to them).
		//
		AppendCharToBuffer(&buffer, ';');

		//----------------------------------------------------------------------
		// We have a fragment. Figure out where it goes.
		//
		printf("We have a fragment: '%s'.\n", buffer.data);

		if (sscanf_s(buffer.data, "%d %d", &column, &row) < 2) break;

		//----------------------------------------------------------------------
		// If the row we want is not the row we have open, close the current
		// file and forget we ever opened it.
		//
		if ((rowFile != NULL) && (lastRow != row))
		{
			fclose(rowFile);
			rowFile = NULL;
		}

		//----------------------------------------------------------------------
		// If the file we want is not open, open it.
		//
		if (NULL == rowFile)
		{
			char fileName[ROWFILE_NAME_BUFFER_LENGTH];

			sprintf_s(fileName, ROWFILE_NAME_BUFFER_LENGTH - 1, FILE_PATT, row);

			fopen_s(&rowFile, fileName, "a");

			if (NULL == rowFile) break;
		}

		fwrite(buffer.data, 1, buffer.end, rowFile);

		lastRow = row;

		ClearBuffer(&buffer);
	}
	while (true);

	if (NULL != rowFile) fclose(rowFile);

	ReleaseBuffer(&buffer);

	return 0;
}
