#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "encryption.h"
#include "buffer.h"


int main(void)
{
	// strings to be compressed
	char* bigHelloWorld = "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhello worldddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd";
	char* smallHelloWorld = "hhheeelllloooo wwwooorrrllldddd";
	char* helloWorld = "hello world";

	// print buffer before encoding
	printf("Original Buffers\n");
	printf("-----------------\n");
	printBuffer(bigHelloWorld, strlen(bigHelloWorld));
	printBuffer(smallHelloWorld, strlen(smallHelloWorld));
	printBuffer(helloWorld, strlen(helloWorld));

	// compression buffers
	char* bigCompressBuffer = returnBuffer(BUFFER);					// simple helper function returns the address of a location in memory for a buffer
	char* smallCompressBuffer = returnBuffer(BUFFER);
	char* noCompressBuffer = returnBuffer(BUFFER);

	// encode and compress the strings
	int bigNumberOfChar = encode(bigHelloWorld, bigCompressBuffer);
	int smallNumberofChar = encode(smallHelloWorld, smallCompressBuffer);
	int noCompression = encode(helloWorld, noCompressBuffer);

	// print buffer after encoding
	printf("Encoded / Compressed Buffers\n");
	printf("-----------------\n");
	printBuffer(bigCompressBuffer, strlen(bigCompressBuffer));
	printBuffer(smallCompressBuffer, strlen(smallCompressBuffer));
	printBuffer(noCompressBuffer, strlen(noCompressBuffer));

	// decode and uncompress strings
	char* bigReturnBuffer = returnBuffer(BUFFER);
	char* smallReturnBuffer = returnBuffer(BUFFER);
	char* noReturnBuffer = returnBuffer(BUFFER);

	bigNumberOfChar = decode(bigCompressBuffer, bigReturnBuffer);
	smallNumberofChar = decode(smallHelloWorld, smallReturnBuffer);
	noCompression = decode(helloWorld, noReturnBuffer);

	// print buffer after decoding
	printf("Decoded / Uncompressed Buffers\n");
	printf("-----------------\n");
	printBuffer(bigReturnBuffer, strlen(bigReturnBuffer));
	printBuffer(smallReturnBuffer, strlen(smallReturnBuffer));
	printBuffer(noReturnBuffer, strlen(noReturnBuffer));

	exit(EXIT_SUCCESS);
}
