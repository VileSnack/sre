//------------------------------------------------------------------------------
// ImageFragment.h
//
// Declares the ImageFragment struct.
//
#ifndef IMAGEFRAGMENT_H
#define IMAGEFRAGMENT_H

#include <stdio.h>

struct ImageFragment
{
	struct ImageFragment* next;
	int column;
	int row;
	int subpixel;
	float depth;
	char *text;
};

struct ImageFragment* ParseImageFragment(FILE*);

#endif
