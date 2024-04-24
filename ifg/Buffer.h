//------------------------------------------------------------------------------
// Buffer.h
//
// Declares the Buffer struct.
//
#ifndef BUFFER_H
#define BUFFER_H
#include <stdbool.h>

struct Buffer
{
	int end;
	int reserved;
	char* data;
};

void AppendCharToBuffer(struct Buffer*, char);
void ClearBuffer(struct Buffer*);
void InitBuffer(struct Buffer*);
bool IsBufferEmpty(struct Buffer*);
void ReleaseBuffer(struct Buffer*);
void TrimTail(struct Buffer*);

#endif
