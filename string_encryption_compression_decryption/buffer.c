#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

char* returnBuffer(int size)													// malloc buffer, memset to '\0', and return
{
	char* returnAllocatedBuffer = (char*)malloc(sizeof(char) * size);
	if (!returnAllocatedBuffer)
		exit(EXIT_FAILURE);
	memset(returnAllocatedBuffer, '\0', size);
	return returnAllocatedBuffer;
}

void printBuffer(char* input, int length)										// simple print to terminal
{
	printf("Buffer\n");
	printf("%s\n", input);
	printf("Length - %d\n\n", length);
}