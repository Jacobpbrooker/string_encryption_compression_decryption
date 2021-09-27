#pragma once

#define BUFFER 500 

int encode(char*, char*);
int decode(char*, char*);
void compressToBuffer(char*, char, int, char);
void pushToBuffer(char*, char, int);
