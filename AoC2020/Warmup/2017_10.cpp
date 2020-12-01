#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

void twist(int circle[], int size, int pinch_start, int pinch_length) {
	for (int i = 0; i < pinch_length/2; i++) {
		int temp = circle[(pinch_start + i) % size];
		circle[(pinch_start + i) % size] = circle[(pinch_start + pinch_length - i - 1) % size];
		circle[(pinch_start + pinch_length - i - 1) % size] = temp;
	}
}



void init(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = i;
	}
}

string knotHash(int circle[]) {
	stringstream stream;
	for (int i = 0; i < 256; i += 16) {
		stream << hex << (circle[i] ^ circle[i + 1] ^ circle[i + 2] ^ circle[i + 3] ^ circle[i + 4] ^ circle[i + 5] ^ circle[i + 6] ^ circle[i + 7] ^ circle[i + 8] ^
			circle[i + 9] ^ circle[i + 10] ^ circle[i + 11] ^ circle[i + 12] ^ circle[i + 13] ^ circle[i + 14] ^ circle[i + 15]);
	}
	return stream.str();
}

int main() {
	const int size = 256;
	int circle [size];
	init(circle, size);

	vector<int> circle2;
	for (int i = 0; i < size; i++)
		circle2.push_back(i);
	

	string s = "206,63,255,131,65,80,238,157,254,24,133,2,16,0,1,3";

	vector<int> characters;

	istringstream is(s);
	char n;
	while (is >> n) 
		characters.push_back((int)n);
	
	characters.push_back(17);
	characters.push_back(31);
	characters.push_back(73);
	characters.push_back(47);
	characters.push_back(23);

	int offset = 0;
	int skip_size = 0;

	for (int i = 0; i < 64; i++) {
		for (int& val : characters) {
			twist(circle, size, offset, val);
			offset = (offset + val + skip_size++) % size;
		}
	}

	cout << knotHash(circle) << endl;
}