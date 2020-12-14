#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <bitset>

using namespace std;

string mask;
map<int, unsigned long long> memory;

int bits = 36;

void apply_mask(int index, unsigned long long value) {
	unsigned long long result = 0;

	//cout << index << endl;
	//cout << value << endl;
	//cout << bitset<64>(value) << endl;
	//cout << mask << endl;

	for (int i = 0; i < bits; i++) {
		//cout << endl << i << endl;
		unsigned long long bit = 0;
		//cout << !!(value & ((static_cast<unsigned long long>(1) << (bits - i - 1)))) << endl;
		if (mask[i] == 'X') { 
			//cout << "X" << endl; 
			bit = !!(value & ((static_cast<unsigned long long>(1) << (bits - i - 1))));
		}
		else { 
			//cout << (mask[i] - '0') << endl; 
			bit = !!(static_cast<unsigned long long>(mask[i] - '0'));
		}

		//cout << bit << endl;
		result |= bit << (bits - i - 1);
		//cout << bitset<64>(result) << endl;

	}
	//cout << bitset<36>(result) << endl << endl;

	
	memory[index] = result;
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_14.txt");

	string key;
	char equals;
	string value;

	int c = 0;
	while (input >> key >> equals >> value) {
		if (key.compare("mask") == 0) mask = value;
		else apply_mask(stoi(key.substr(4, key.size() - 2)), stoull(value));
		c++;
		//if (c >10) break;
	}

	unsigned long long sum = 0;
	for (pair<int, unsigned long long> p : memory) {

		sum += p.second;
		cout << p.first << ": " << bitset<64>(p.second)  << ", " << p.second << endl;

	}
	cout << sum << endl;

	// 27900215415 too low

	// hamster 11179633149677 
	//		   85732624109
	//		   27900213843
	//		   84683524267

}