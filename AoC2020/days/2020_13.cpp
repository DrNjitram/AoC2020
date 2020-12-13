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

// Function for extended Euclidean Algorithm  
int gcdExtended(int a, int b, int* x, int* y)
{
	// Base Case  
	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return b;
	}

	int x1, y1; // To store results of recursive call  
	int gcd = gcdExtended(b % a, a, &x1, &y1);

	// Update x and y using results of  
	// recursive call  
	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_13.txt");

	int departure;

	input >> departure;

	vector<pair<int, int>> schedules;

	string x;

	int i = 0;
	while (getline(input, x, ',')) {
		if (x.compare("x") != 0) schedules.push_back(pair<int, int>(i, stoi(x))); 
		i++;
	}
	

	vector<int> wait_times;

	int min = departure;
	int max = 0;
	int mindex = -1;
	int maxdex = -1;
	unsigned long long multiple = 1;

	for (int i = 0; i < schedules.size(); i++){
		int v = schedules[i].second;
		int waiting = v - (departure % v);
		if (waiting < min) {
			min = waiting;
			mindex = v;
		}
		if (v > max) {
			max = v; 
			maxdex = schedules[i].first;
		}
		multiple *= v;
	}

	cout << "Part 1:" << mindex * min << endl;

	
	int x_, y, a = schedules[0].second, b = schedules[1].second;
	int g = gcdExtended(a, b, &x_, &y);

	cout << x_ << ", "<< y << endl;


	unsigned long long timestamp = 0;
	unsigned long long increment;

	bool found = false;

	while (!found) {
		increment = 1;
		found = true;
		for(pair<int, int> v : schedules){
			if (((timestamp + v.first) % v.second) != 0) found = false;
			else increment *= v.second;
		}
		if(!found) timestamp += increment;
	}

	cout << timestamp;

}