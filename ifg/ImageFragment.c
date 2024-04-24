//------------------------------------------------------------------------------
// ImageFragment.cpp
//
// Implements the ImageFragment struct.
//
#include <stdio.h>
#include "ImageFragment.h"
#include "Buffer.h"

//------------------------------------------------------------------------------
// ImageFragment.c
//
// Implements the ImageFragment functions.
//
#include "ImageFragment.h"

struct ImageFragment* ParseImageFragment(FILE* input)
{
	struct Buffer buffer;
	char* text = NULL;

	InitBuffer(&buffer);

	ParseUntilCharacter(&buffer, ';');

	return NULL;
}
