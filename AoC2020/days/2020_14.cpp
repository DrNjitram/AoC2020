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
#include <numeric>

using namespace std;

map<unsigned long long, unsigned long long> memory;

int bits = 36;

vector<string> permutate(string mask) {
	vector<string> permutations;
	permutations.push_back(mask);

	bool finish = false;

	while (!finish) {
		finish = true;
		int size = permutations.size();
		for (int j = 0; j < size; j++) {
			string s = permutations[j];
			for (int i = 0; i < s.size(); i++) {
				if (s[i] == 'X') {
					finish = false;				
					s[i] = '1';
					permutations.push_back(s);
					s[i] = '0';
					permutations[j] = s;
				}
			}
		}
	}

	return permutations;
}


string apply_mask(string mask, unsigned long long index) {
	string result = "000000000000000000000000000000000000";

	for (int i = 0; i < bits; i++) {
		char bit;

		if (mask[i] == 'X') bit = 'X';	
		else if(mask[i] == '1') bit = '1';	
		else bit = '0' + !!(index & ((1LL << (bits - i - 1))));

		result[i] = bit;
	}

	return result;
}

void write_mem(unsigned long long adress, unsigned long long value, string mask) {
	string result = apply_mask(mask, adress);
	
	vector<string> perms = permutate(result);

	for (string mask : perms) 
		memory[bitset<36>(mask).to_ullong()] = value;
	
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_14.txt");

	string key;
	char equals;
	string mask;
	string value;

	auto start = chrono::high_resolution_clock::now();

	while (input >> key >> equals >> value) {
		if (key.compare("mask") == 0) mask = value;
		else write_mem(stoull(key.substr(4, key.size() - 2)), stoull(value), mask);
	}

	unsigned long long result = accumulate(memory.cbegin(), memory.cend(), 0LL, [](auto a, auto b) { return a + b.second; });

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << result << endl;

	cout << "Time(us): " << duration.count() << endl;
}

