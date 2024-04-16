//------------------------------------------------------------------------------
// Subpixel.h
//
// Declares the Subpixel structure.
//
#ifndef SUBPIXEL_H
#define SUBPIXEL_H
#include "ImageFragment.h"

struct Subpixel
{
	//-----------------------------------------------------------------------------
	// This is the head of a linked list.
	//
	struct ImageFragment* fragments;
};
#endif
