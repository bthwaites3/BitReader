#include "bitreader.h"
#include "bitreader.tcc"

using namespace std;

int main()
{
	char* filename = "../inputs/testfile.bin";
	bitreader<short> reader;
	reader.open(filename);
	short result = 0;
	result = reader.read(8);
	cout << "First Result: " << hex << result << endl;
	result = reader.read(8);
	cout << "Second Result: " << hex << result << endl;
	result = reader.read(8);
	cout << "Result: " << hex << result << endl;
	result = reader.read(8);
	cout << "Result: " << hex << result << endl;
	result = reader.read(8);
	cout << "Result: " << hex << result << endl;
	result = reader.read(8);
	cout << "Result: " << hex << result << endl;
	result = reader.read(8);
	cout << "Result: " << hex << result << endl;
	return 0;
}
