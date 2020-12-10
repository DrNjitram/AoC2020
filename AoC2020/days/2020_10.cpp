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

using namespace std;

vector<int> adapters;

void part1() {
	int jumps[] = { 0, 0, 0, 0 };

	int cur_voltage = 0;

	for (int& v : adapters) {
		cout << v << endl;
		int jmp = v - cur_voltage;
		cur_voltage = v;
		if (jmp > 3) cout << "!" << endl;
		jumps[jmp]++;
	}

	cout << jumps[1] << " * " << jumps[3] << " = " << jumps[1] * jumps[3] << endl;
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_10.txt");
	stringstream buffer;
	buffer << input.rdbuf();
	istringstream is(buffer.str());

	int n;
	


	while (is >> n)
		adapters.push_back(n);

	adapters.push_back(0);
	sort(adapters.begin(), adapters.end());
	adapters.push_back(adapters[adapters.size() - 1] + 3);
	
	

	
	part1();

	//return 0;

	adapters.push_back(0);
	adapters.push_back(0);
	adapters.push_back(0);
	
	const int size = 94 + 2 + 3;

	unsigned long long int ways[size];

	for (int i = 0; i < size; i++) {
		ways[i] = 0;
	}

	ways[0] = 1;

	for (int i = 0; i < adapters.size()-3; i++) {
		if (adapters[i + 1] - adapters[i] < 4) ways[i + 1] += ways[i];
		if (adapters[i + 2] - adapters[i] < 4) ways[i + 2] += ways[i];
		if (adapters[i + 3] - adapters[i] < 4) ways[i + 3] += ways[i];
	}
	cout << ways[size-4] << endl;
}