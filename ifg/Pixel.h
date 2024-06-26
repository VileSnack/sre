//------------------------------------------------------------------------------
// Pixel.h
//
// Declares the Pixel object.
//
#ifndef PIXEL_H
#define PIXEL_H

#include <stdbool.h>
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

bool CreatePixels();
void DestroyPixels();

bool InitializePixel(struct Pixel*);
void FinalizePixel(struct Pixel*);

void ProcessImageFragmentFile(FILE*);
void AddFragmentToPixel(struct ImageFragment*);
void OutputRow();

#endif
