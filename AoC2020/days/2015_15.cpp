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

vector<int> turns;

int find_val(int v, int turn) {
	for (int i = turns.size() - 2; i >= 0; i--) {
		if (turns[i] == v) return turn - i - 1;
	}
	return 0;
}

int main() {

	string input = "0 3 6";
	istringstream is(input);

	int n;
	while (is >> n) {
		turns.push_back(n);
		//cout << n << endl;
	}

	int turn_limit = 30000000;
	int last_said = turns[turns.size() - 1];


	for (int i = turns.size(); i < turn_limit; i++) {
		last_said = find_val(last_said, i);
		//cout <<  i + 1 << ": " << last_said << endl;
		turns.push_back(last_said);
	}

	cout << last_said << endl;
}