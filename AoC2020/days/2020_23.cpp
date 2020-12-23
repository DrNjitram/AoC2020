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
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <deque>

using namespace std;
using ULL = unsigned long long;

int main() {
	const string input = "389125467";

	const unsigned long long total_cups = 1000000;
	//total_cups = 9;

	const unsigned long long turns = 10'0;//10'000'000

	vector<unsigned long long> cups;
	cups.reserve(total_cups);

	const unsigned long long current_cup = 1;

	for (const char& c : input) 
		cups.push_back(c - (int)'0');

	

	for (unsigned long long i = input.length(); i < total_cups; i++) {
		cups[i] = i + 1;
	}

	rotate(cups.begin(), cups.end() - 1, cups.end());

	auto start = chrono::high_resolution_clock::now();

	for (unsigned long long i = 0; i < turns; i++) {
		unsigned long long destination_cup_value = (cups[current_cup] - 1);
		if (destination_cup_value == 0) destination_cup_value = total_cups;
		unsigned long long destination_cup = 0;

		rotate(cups.begin(), cups.begin() + current_cup, cups.end());

		array<unsigned long long, 3> pickup;

		copy(cups.begin() + 1, cups.begin() + 4, pickup.begin());

		cups.erase(cups.begin() + 1, cups.begin() + 4);

		for (int _ = 0; _ < 3; _++) {
			if (destination_cup_value == pickup[0] ||
				destination_cup_value == pickup[1] ||
				destination_cup_value == pickup[2]
				)destination_cup_value--;
			if (destination_cup_value == 0) destination_cup_value = total_cups;
		}

		vector<ULL>::iterator it = find(cups.begin(), cups.end(), destination_cup_value);
		ULL index = distance(cups.begin(), it);

		cups.insert(cups.begin() + index + 1, pickup.begin(), pickup.end());
	}



	unsigned long long answer = 1;
	answer *= cups[1];
	answer *= cups[2];

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

	/*
	for (ULL ull : cups)
		cout << ull;
	cout << endl;*/

	cout << answer << endl;
	cout << "Time(ms): " << duration.count() << endl;

	// debug ans 158802
}