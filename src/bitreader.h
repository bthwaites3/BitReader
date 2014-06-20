#pragma once

#include <stdlib.h>
#include <iostream>
#include <stdint.h>

template <typename T>
class bitreader
{
public:
	bitreader();
	~bitreader(){}

	void open(const char* filename, const char* mode);
	void reset();
	void seek(long int offset, int origin);
	size_t read(T* buffer, size_t length);
	size_t fwrite(T* buffer, size_t length);

private:
	FILE* ptr;
	unsigned short bitOffset;
	long int fileSize;
	T currentChunk;

	T read_single(unsigned int length);

};
