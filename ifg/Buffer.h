//------------------------------------------------------------------------------
// Buffer.h
//
// Declares the Buffer struct.
//
#ifndef BUFFER_H
#define BUFFER_H
#include <stdbool.h>
#include <stdio.h>

struct Buffer
{
	int end;
	int reserved;
	char* data;
};

void AppendCharToBuffer(struct Buffer*, const char);
void ClearBuffer(struct Buffer*);
void InitBuffer(struct Buffer*);
bool IsBufferEmpty(struct Buffer*);
void ParseUntilCharacter(struct Buffer*, FILE*, const char);
void ReleaseBuffer(struct Buffer*);
void TrimTail(struct Buffer*);

#endif
