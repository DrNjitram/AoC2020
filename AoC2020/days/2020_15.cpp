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

	int turn_limit = 30000001;

	auto start = chrono::high_resolution_clock::now();

	for (int i = turns.size() + 1; i < turn_limit; i++) {
		pair<int, int> p = turns[last_said];
		last_said = p.second == 0 ? 0 : p.first - p.second;
		//if (i % 100000 == 0) cout << i << endl;
		turns[last_said] = pair<int, int>(i, turns[last_said].first);
	}

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds>(stop - start);

	cout << last_said << endl;

	cout << "Time(ss): " << duration.count() << endl;
}