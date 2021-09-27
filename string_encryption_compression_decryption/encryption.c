#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encryption.h"
#include "conversion.h"

#define MAXINTFORCHAR 254																		// max int for a single char
#define READNEXTANDSUM 255																		// if 255 is written, consider it 254 and read+sum the next int as well
#define ESCAPECHARACTER 0x1b																	// escape character is ESC character
#define RUN 3																					// only want runs > 3
#define CHARACTERRESET 1																		// minimum there will be 1 character being read


int encode(char* inputBuffer, char* outputBuffer)
{
	int characterRun = CHARACTERRESET;															// initialize the character run 
	unsigned char escapeCharacter = ESCAPECHARACTER;														

	for (unsigned int i = 0; i < strlen(inputBuffer); i++)										// loop as many times as the string length of the input
	{
		int j = i + 1;																			// set j to the position after i 
		
		if (inputBuffer[i] == inputBuffer[j])													// current position and next position are the same
			characterRun++;																		// increment the character run
		else if (inputBuffer[i] != inputBuffer[j])												// current position and the next position are different 
		{
			if (characterRun > RUN)																// greater than 3 makes it a run (I do not want to equal 3)
			{													
				compressToBuffer(outputBuffer, escapeCharacter, characterRun, inputBuffer[i]);	// because it is a run and we are at the end of the run we need to write that data to the output buffer
				characterRun = CHARACTERRESET;													// reset the character
			}
			else
			{																					// the current char is different from the next character AND it is not a run
				pushToBuffer(outputBuffer, inputBuffer[i], characterRun);						// write the current character to output buffer
				characterRun = CHARACTERRESET;													// reset the character run
			}
		}
	}
																				
	return strlen(outputBuffer);																// return the number of characters in the compressed buffer
}

int decode(char* inputBuffer, char* outputBuffer)
{
	int characterRun;
	char writeChar = '\0';

	for (unsigned int i = 0; i < strlen(inputBuffer); i++)										// loop for the length of the inputBuffer
	{
		
		if (inputBuffer[i] == ESCAPECHARACTER)													// inputBuffer[] is the escape character
		{
			characterRun = 0;
			i++;																				// hit escape character, increment to get the number
			while (charToInt(inputBuffer[i]) == READNEXTANDSUM)									// READNEXTANDSUM is 255 which signals to place number in buffer and prepare to place another number in the buffer as well
			{
				characterRun += charToInt(inputBuffer[i]);
				--characterRun;																	// 255 means that > 254 has been written, I need to minus 1 to get the correct number and then sum with next value
				i++;																			// incremement to the buffer to the next position to read again
			}
			
			characterRun += charToInt(inputBuffer[i]);											// add the rest of the run

			pushToBuffer(outputBuffer, inputBuffer[++i], characterRun);							// push the amount of characters back to the new buffer
		}
		else
		{
			characterRun = CHARACTERRESET;
			pushToBuffer(outputBuffer, inputBuffer[i], characterRun);							// not a run and just push to the buffer
		}
	}

	return strlen(outputBuffer);																// return the number of characters in the uncompressed buffer
}

void compressToBuffer(char* buffer, char escape, int run, char character)						// push the run of characters to the end of the buffer 
{
	int i = 0;
	while (buffer[i] != '\0')
	{
		i++;
		if (i > BUFFER)																			// if x is about to be larger than the buffer we exit without writing
			return;
	}

	buffer[i] = escape;																			// place the escape character in buffer
	
	if (run > MAXINTFORCHAR)
	{
		int loops = run / MAXINTFORCHAR;
		
		for (int j = 0; j < loops; j++)
		{
			buffer[++i] = intToChar(READNEXTANDSUM);						
		}

		buffer[++i] = intToChar(run % MAXINTFORCHAR);
	}
	else
		buffer[++i] = intToChar(run);

	buffer[++i] = character;
}

void pushToBuffer(char* buffer, char character, int run)										// find end of the string and add character there
{
	int x = 0;
	while (buffer[x] != '\0')
	{
		x++;
		if (x > BUFFER)																			// if x is about to be larger than the buffer we exit without writing
			return;
	}

	for(int i = 0; i < run; i++)
		buffer[x+i] = character;
}