#pragma once

#include <stdlib.h>
#include <iostream>
#include <stdint.h>

template <typename T>
class bitreader
{
public:
	bitreader() : bitOffset(0){}
	~bitreader(){}

	void open(char* filename);
	void reset();

	size_t read(T* buffer, size_t length);
	void seek(long int offset, int origin);

private:
	FILE* ptr;
	unsigned short bitOffset;
	long int fileSize;
	T currentChunk;

	T read_single(unsigned int length);

};
