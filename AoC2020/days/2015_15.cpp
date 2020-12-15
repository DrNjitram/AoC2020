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

map<int, pair<int, int>> turns; // value seen last at turns n0 and before that at turn n1

int main() {
	istringstream is("6 4 12 1 20 0 16");

	int i = 0;
	int last_said;

	while (is >> last_said) 
		turns[last_said] = pair<int, int>(++i, 0);	

	int turn_limit = 2021;
	
	for (int i = turns.size() + 1; i < turn_limit; i++) {
		last_said = turns[last_said].second == 0 ? 0 : turns[last_said].first - turns[last_said].second;
		if (i % 100000 == 0) cout << i << endl;
		turns[last_said] = pair<int, int>(i, turns[last_said].first);
	}

	cout << last_said << endl;
}