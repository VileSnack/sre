//------------------------------------------------------------------------------
// Pixel.cpp
//
// Implements the Pixel struct.
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Pixel.h"
#include "Subpixel.h"

extern int xMin;
extern int xMax;

struct Pixel* pixels = NULL;

bool SetUpPixels()
{
	int index;
	bool success = true;
	
	pixels = malloc(sizeof(struct Pixel) * (xMax - xMin + 1));

	if (NULL == pixels)
	{
		fprintf(stderr, "***** Error: Failed to reserve %d bytes for pixel array.\n",
			(int)(sizeof(struct Pixel) * (xMax - xMin + 1))
		);

		return false;
	}

	for (index = 0; index <= xMax - xMin; index++)
	{
		pixels[index].subpixels = NULL;
	}

	for (index = 0; index <= xMax - xMin; index++)
	{
		if (!InitPixel(pixels + index)) success = false;
	}

	if (success) return true;

	for (index = 0; index <= xMax - xMin; index++)
	{
		FreeSubpixels(pixels[index].subpixels);
	}
}
