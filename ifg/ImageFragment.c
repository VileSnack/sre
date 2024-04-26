//------------------------------------------------------------------------------
// ImageFragment.cpp
//
// Implements the ImageFragment struct.
//
#include <stdio.h>
#include <stdlib.h>
#include "ImageFragment.h"
#include "Buffer.h"
#include "Pixel.h"

//------------------------------------------------------------------------------
// ImageFragment.c
//
// Implements the ImageFragment functions.
//
#include "ImageFragment.h"

struct ImageFragment* ParseImageFragment(FILE* input)
{
	struct Buffer buffer;
	struct ImageFragment* fragment = NULL;

	InitBuffer(&buffer);

	ParseUntilCharacter(&buffer, input, ';');

	if (!IsBufferEmpty(&buffer))
	{
		fragment = malloc(sizeof (struct ImageFragment));

		if (NULL == fragment)
		{
			fprintf(stderr, "Error: Unable to reserve %d bytes for ImageFragment object.\n", (int)sizeof (struct ImageFragment));
		}
		else
		{
			//------------------------------------------------------------------
			// Pass ownership of parsed text to the image fragment.
			//
			fragment->text = buffer.data;
			buffer.data = NULL;

			if (4 > sscanf_s(fragment->next, "%d %d %d %f", &fragment->column, &fragment->row, &fragment->subpixel, &fragment->depth))
			{
				fprintf(stderr, "Error: Scan failure for image fragment: '%s'.\n", fragment->text);
				free(fragment);
				fragment = NULL;
			}
			else
			{
				//------------------------------------------------------------------
				// Ensure that releasing the buffer will not free the parsed text.
				//
				buffer.data = NULL;
				AddFragmentToPixel(fragment);
			}
		}
	}

	ReleaseBuffer(&buffer);

	return fragment;
}
