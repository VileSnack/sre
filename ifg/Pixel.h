//------------------------------------------------------------------------------
// Pixel.h
//
// Declares the Pixel object.
//
#ifndef PIXEL_H
#define PIXEL_H

#include <stdio.h>
#include "ImageFragment.h"
#include "Subpixel.h"

struct Pixel
{
	//--------------------------------------------------------------------------
	// This points to an array.
	//
	struct Subpixel* subpixels;
};

void AddFragmentToPixel(struct ImageFragment*);
void SetUpPixels();
void ProcessImageFragmentFile(FILE*);
void OutputRow();
void FreePixels();

#endif
