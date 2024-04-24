//------------------------------------------------------------------------------
// Buffer.c
//
// Implements functions for the Buffer struct.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Buffer.h"

#define DEFAULT_BUFFER_LENGTH 16

void AppendCharToBuffer(struct Buffer* buffer, char c)
{
	if (NULL == buffer) return;
	
	if (NULL == buffer->data)
	{
		buffer->data = malloc(DEFAULT_BUFFER_LENGTH);

		if (NULL == buffer->data)
		{
			fprintf(stderr
				, "***** Error: Unable to reserve 16 bytes for Buffer object.\n");
			return;
		}

		buffer->end = 0;
		buffer->reserved = DEFAULT_BUFFER_LENGTH;
		*(buffer->data) = '\0';
	}

	if (buffer->end + 1 >= buffer->reserved)
	{
		char* newBuffer = NULL;
		int newLength;

		newLength = buffer->reserved * 2;
		newBuffer = malloc(newLength);

		if (NULL == newBuffer)
		{
			fprintf(stderr
				, "***** Error: Unable to reserve %d bytes for Buffer object.\n"
				, newLength);
			return;
		}

		strcpy(newBuffer, buffer->data);

		free(buffer->data);
		buffer->data = newBuffer;
		buffer->reserved = newLength;
	}

	buffer->data[buffer->end] = c;
	buffer->end++;
	buffer->data[buffer->end] = '\0';
}

void ClearBuffer(struct Buffer* buffer)
{
	if (NULL != buffer)
	{
		buffer->data[0] = '\0';
		buffer->end = 0;
	}
}

void InitBuffer(struct Buffer* buffer)
{
	if (NULL != buffer)
	{
		buffer->data = NULL;
	}
}

bool IsBufferEmpty(struct Buffer* buffer)
{
	if (NULL == buffer) return true;

	if (NULL == buffer->data) return true;

	return (0 == buffer->end);
}

void ReleaseBuffer(struct Buffer* buffer)
{
	if (NULL != buffer)
	{
		free(buffer->data);
	}
}

void TrimTail(struct Buffer* buffer)
{
	if (NULL != buffer)
	{
		while (buffer->data[buffer->end - 1] <= ' ')
		{
			buffer->end--;
			buffer->data[buffer->end] = '\0';
		}
	}
}
