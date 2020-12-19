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

using namespace std;

regex rule("(\\([^\\(\\)]+\\))");
regex add_rule("(\\d+ \\+ \\d+)");


string evaluate(string s, bool recursive) {

	if (recursive) {
		smatch sm;
		regex_search(s, sm, add_rule);
		if (sm.size() > 0) {
			do {
				s = regex_replace(s, add_rule, evaluate(sm[1], false), regex_constants::format_first_only);
				regex_search(s, sm, add_rule);
			} while (sm.size() > 0);
		}
	}
	
	istringstream is(s);

	unsigned long long n;
	char c;

	unsigned long long accumulator;
	is >> accumulator;

	while (is >> c >> n) {
		if (recursive && c == '*') accumulator *= n;
		else accumulator += n;		
	}

	return to_string(accumulator);
}


int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\Advent Of Code\\AoC2020\\AoC2020\\input\\2020_18.txt");

	string x;
	smatch sm;
	unsigned long long answer = 0;


	auto start = chrono::high_resolution_clock::now();

	while (getline(input, x)) {

		regex_search(x, sm, rule);
		if (sm.size() > 0) {
			do {
				x = regex_replace(x, rule, evaluate(sm[0].str().substr(1, sm[0].length() - 2), true), regex_constants::format_first_only);

				regex_search(x, sm, rule);
			} while (sm.size() > 0);
		}
		answer += stoull(evaluate(x, true));
	}

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << answer << endl;
	cout << "Time(us): " << duration.count() << endl;
}