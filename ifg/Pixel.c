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

extern int samplingLevel;
extern int xMin;
extern int xMax;

struct Pixel* pixels = NULL;

//------------------------------------------------------------------------------
// Creates the Pixel array.
//
bool CreatePixels()
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
		FreeSubpixels(pixels[index]);
	}

	return false;
}

//------------------------------------------------------------------------------
// Frees up the Pixel array.
//
void DestroyPixels()
{
	int index;

	if (NULL == pixels) return;

	for (index = xMin; index <= xMax; index++)
	{
		FinalizePixel(pixels + (index - xMin));
	}

	free(pixels);
}

//------------------------------------------------------------------------------
// Initializes a pixel (i.e., creates its subpixel array).
//
bool InitPixel(struct Pixel* pixel)
{
	int index;

	pixel->subpixels = malloc(sizeof(struct Subpixel) * samplingLevel);

	if (NULL == pixel->subpixels)
	{
		fprintf(stderr, "***** Error: Failed to reserve %d bytes for subpixel array.\n",
			(int)(sizeof(struct Subpixel) * samplingLevel)
		);

		return false;
	}

	for (index = 0; index < samplingLevel; index++)
	{
		pixel->subpixels[index].fragments = NULL;
	}

	return true;
}

//------------------------------------------------------------------------------
// Frees the resources used by a Pixel. The Pixel struct itself is not freed.
//
void FreePixel(struct Pixel* pixel)
{
	int index;

	if (NULL == pixel) return;

	if (NULL == pixel->subpixels) return;

	for (index = 0; index < samplingLevel; index++)
	{
		FreeSubpixel(pixel->subpixels + index);
	}

	free(pixel->subpixels);
}

