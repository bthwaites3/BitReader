#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdint.h>

template <class T>
class bitreader
{
public:
	bitreader() : bitOffset(0){}
	~bitreader(){}

	void open(char* filename);
	void reset();

	T read(unsigned int length);

private:
	FILE* ptr;
	unsigned short bitOffset;
	long int fileSize;
	T currentChunk;

	int is_big_endian(void);
};
