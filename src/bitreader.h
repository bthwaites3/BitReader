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

	int read(unsigned int length);
	void seek(unsigned int position);

private:
	FILE* ptr;
	unsigned short bitOffset;
	long int fileSize;
	T currentChunk;

	int is_big_endian(void);
	T read_single(unsigned int length);

};
