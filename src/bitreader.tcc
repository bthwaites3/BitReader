#include "bitreader.h"

using namespace std;

template <class T>
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
template <class T>
int bitreader<T>::read(unsigned int length)
{
	int elementsRequested = (sizeof(T) * 8) / length;
}

template <class T>
void bitreader<T>::reset()
{
	bitOffset = 0;
	fseek(ptr, 0, SEEK_SET);
}


template <class T>
void bitreader<T>::seek(unsigned int position)
{

}

template <class T>
int bitreader<T>::is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1; 
}

//Read bits into the buffer. Length is the desired number of bits.
//Right now limit the buffer to one T.
template <class T>
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
		tmpLower = currentChunk >> numBits - bitsRemaining;
		retChunk = retChunk + tmpLower;
		//cout << hex << retChunk << dec << endl;
	} 

	//Now apply the bit mask
	T bitmask = (1 << length) - 1;
	retChunk = retChunk & bitmask;

	//Update the bit offset
	bitOffset = (bitOffset + length) % numBits;
	//cout << "New Offset: " << dec << bitOffset << endl;
	return retChunk;
}

