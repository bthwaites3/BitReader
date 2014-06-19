#include "bitreader.h"
#include "../tools/utils.h"

using namespace std;

template <typename T>
void bitreader<T>::open(char* filename)
{
	if(is_big_endian())
		cout << "Running on a Big Endian machine!" << endl;
	else
		cout << "Running on a Little Endian machine!" << endl;

	ptr = fopen(filename, "r");
	fseek(ptr, 0, SEEK_END);
	fileSize = ftell(ptr);
	fseek(ptr, 0, SEEK_SET);
	fread(&currentChunk, sizeof(T), 1, ptr);
}

// This is basically a wrapper for the read_single function
template <typename T>
size_t bitreader<T>::read(T* buffer, size_t length)
{
	if( (int)length < 0 )
	{
		cout << "Error: Cannot read negative length!" << endl;
		length = 0;
	}
	float elementsFloat = (float)length / (float)(sizeof(T) * 8);
	int elementsRequested = posIntCeil(elementsFloat);
	size_t bitsRemaining = length;
	cout << "Requested " << dec << elementsRequested << " elements" << endl;
	for (int ii = 0; ii < elementsRequested; ii++)
	{
		size_t nextReadLength = (bitsRemaining > sizeof(T) * 8) ?
			(sizeof(T) * 8) : bitsRemaining;
		T retSingle = read_single (nextReadLength);
		buffer[ii] = retSingle;
		bitsRemaining = bitsRemaining - nextReadLength;
	}
	return elementsRequested;
}

template <typename T>
void bitreader<T>::reset()
{
	bitOffset = 0;
	fseek(ptr, 0, SEEK_SET);
}


template <typename T>
void bitreader<T>::seek(long int offset, int origin)
{
	long int newBitPos;
	if(origin == SEEK_CUR)
		newBitPos = (ftell(ptr) * 8) - (sizeof(T) * 8) + bitOffset + offset;
	else if(origin == SEEK_SET)
		newBitPos = offset;
	else if(origin == SEEK_END)
		newBitPos = (fileSize * 8) + offset;
	else
	{
		cout << "Error: Seek given an invalid origin parameter." << endl;
		return;
	}

	bitOffset = newBitPos % 8;
	long int newByteIndex = newBitPos / 8;

	fseek(ptr, newByteIndex, SEEK_SET);
	fread(&currentChunk, sizeof(T), 1, ptr);
}

//Read bits into the buffer. Length is the desired number of bits.
//Right now limit the buffer to one T.
template <typename T>
T bitreader<T>::read_single(unsigned int length)
{
	T retChunk = currentChunk;
	unsigned int numBits = sizeof(T) * 8;

	if(length > numBits)
	{
		cout << "Tried to read too many bits!" << endl;
		return 0;
	}

	if((bitOffset + length) <= numBits)
	//Only operate on the current chunk of data
	{
		retChunk = retChunk >> (numBits - (bitOffset + length));
		if((bitOffset + length) == numBits)
		{
			fread(&currentChunk, sizeof(T), 1, ptr);
		}

	}else
	//Read another chunk of data
	{
		T tmpLower;
		unsigned short bitsRemaining = length - (numBits - bitOffset);
		retChunk = retChunk << bitsRemaining;
		fread(&currentChunk, sizeof(T), 1, ptr);
		tmpLower = currentChunk >> (numBits - bitsRemaining);
		retChunk = retChunk + tmpLower;
	}

	//Now apply the bit mask
	T bitmask = (1 << length) - 1;
	retChunk = retChunk & bitmask;

	//Update the bit offset
	bitOffset = (bitOffset + length) % numBits;
	return retChunk;
}
