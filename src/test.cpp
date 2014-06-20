#include "bitreader.h"
#include "bitreader.tcc"

#define ELEMENTS 10

using namespace std;

int main()
{
	char filename[] = "../inputs/testfile.bin";
	bitreader<char> reader;
	reader.open(filename, "r");
	char* returnBuffer = (char*)malloc(8 * sizeof(char));
	for (int ii = 0; ii < 8; ii++)
	{
		returnBuffer[ii] = 0;
	}
	size_t result;
	reader.seek(320, SEEK_SET);
	result = reader.read(returnBuffer, 8*ELEMENTS);
	for (int ii = 0; ii < ELEMENTS; ii++)
	{
		cout << "Result " << hex << ii << ": " << returnBuffer[ii] << endl;
	}

	cout << "######" << endl;

	reader.seek(-80, SEEK_CUR);
	result = reader.read(returnBuffer, 8*ELEMENTS);
	for (int ii = 0; ii < ELEMENTS; ii++)
	{
		cout << "Result " << hex << ii << ": " << returnBuffer[ii] << endl;
	}

	cout << "######" << endl;

	reader.seek(496, SEEK_CUR);
	result = reader.read(returnBuffer, 48);
	for (int ii = 0; ii < 6; ii++)
	{
		cout << "Result " << hex << ii << ": " << returnBuffer[ii] << endl;
	}
	return 0;
}
