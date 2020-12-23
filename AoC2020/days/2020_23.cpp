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
	string input = "389125467";


	unsigned long long total_cups = 1000000;
	deque<unsigned long long> cups;

	for (char& c : input) 
		cups.push_back(c - (int)'0');


	unsigned long long current_cup = 0;
	
	cups.resize(total_cups);
	for (unsigned long long i = input.length(); i < total_cups; i++) {
		cups[i] = i + 1;
	}

	

	unsigned long long turns = 10000000;
	turns = 100;

	auto start = chrono::high_resolution_clock::now();

	for (unsigned long long i = 0; i < turns; i++) {
		unsigned long long destination_cup_value = (cups[current_cup] - 1);
		if (destination_cup_value == 0) destination_cup_value = total_cups;
		unsigned long long destination_cup;

		rotate(cups.begin(), cups.begin() + current_cup, cups.end());

		array<unsigned long long, 3> pickup = {
			cups[1],
			cups[2],
			cups[3]
		};

		cups.erase(cups.begin() + 1, cups.begin() + 4);

/*
		unordered_map<unsigned long long, unsigned long long> set_cups;

		
		for (unsigned long long i = 0; i < total_cups - 3; i++) {
			set_cups[cups[i]] = i;
		}
		

		ULL index = 0;
		for (deque<ULL>::iterator it = cups.begin(); it != cups.end(); ++it)
			set_cups[*it] = index++;

		while (true) {
			unordered_map<unsigned long long, unsigned long long>::iterator it = set_cups.find(destination_cup_value);
			if (it != set_cups.end()) {
				destination_cup = it->second;
				break;
			}
			else {
				destination_cup_value--;
				if (destination_cup_value < 1) destination_cup_value = total_cups;
			}
		}*/

		
		bool finished = false;
		while (!finished) {
			ULL index = 0;
			for (deque<ULL>::iterator it = cups.begin(); it != cups.end(); ++it, index++) {
				if (*it == destination_cup_value) {
					destination_cup = index;
					finished = true;
					break;
				}
			}
			if (!finished) {
				destination_cup_value--;
				if (destination_cup_value < 1) destination_cup_value = total_cups;
			}
		}


		cups.insert(cups.begin() + destination_cup + 1, pickup.begin(), pickup.end());

		current_cup = 1;
	}



	unsigned long long answer = 1;
	answer *= cups[1];
	answer *= cups[2];

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);


	cout << answer << endl;
	cout << "Time(ms): " << duration.count() << endl;

	// debug ans 158802
}