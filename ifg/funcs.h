//------------------------------------------------------------------------------
// funcs.h
//
// Declares the functions in the app.
//
#ifndef FUNCS_H
#define FUNCS_H

#include <stdbool.h>
#include <stdio.h>

bool ParseCommandLine(int, char**);
void ProcessImageFragmentFile(FILE*);
#endif
