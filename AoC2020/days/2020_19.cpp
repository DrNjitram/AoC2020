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

using Pair = pair<vector<int>, vector<int>>;

unordered_map<int, Pair> rules;




vector<string> combine_v(vector<string> v1, vector<string> v2) {
	if (v1.size() == 0) return v2;
	vector<string> result;

	for (string s1 : v1) {
		for (string s2 : v2) {
			result.push_back(s1 + s2);
		}
	}
	return result;
}

vector<string> rule_search(int n) {
	vector<string> result;
	vector<string> result2;

	Pair rule = rules[n];

	if (rule.first.size() > 0) {
		if (rule.second.size() == 0) {
			for (int& v : rule.first) {
				result = combine_v(result, rule_search(v));
			}
			return result;
		}
		else {
			for (int& v : rule.first) {
				result = combine_v(result, rule_search(v));
			}
			for (int& v : rule.second) {
				result2 = combine_v(result2, rule_search(v));
			}
			vector<string> result12;
			result12.reserve(result.size() + result2.size()); // preallocate memory
			result12.insert(result12.end(), result.begin(), result.end());
			result12.insert(result12.end(), result2.begin(), result2.end());

			return result12;
		}
	}
	else {
		result.push_back(string(1, rule.second[0]));
		return result;		
	}
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\Advent Of Code\\AoC2020\\AoC2020\\input\\2020_19.txt");

	string x;

	while (getline(input, x)) {
		if (x.compare("") == 0) break;
		cout << x << endl;

		int rule_no;

		Pair p;

		for (int i = 0; i < x.length(); i++) {
			char c = x[i];
			if (c == ':') {
				rule_no = stoi(x.substr(0, i));

				if (x[i+2] == '\"') {
					p.second.push_back(x[i + 3]);
					break;
				}
				else {
					istringstream is(x.substr(i+1, x.length()));
					string substr;
					vector<int> cur_rule;

					while (is >> substr) {
						if (substr.compare("|") == 0) {
							p.second = cur_rule;
							cur_rule.clear();
						}
						else {
							cur_rule.push_back(stoi(substr));
						}
					}
					p.first = cur_rule;
					break;
				}
			} 			 
		}
		rules[rule_no] = p;
	}

	vector<string> valid = rule_search(0);
	set<string> valid_s;

	for (string s : valid) {
		valid_s.insert(s);
	}

	int answer = 0;
	while (getline(input, x)) {
		cout << x << endl;
		
		if (valid_s.find(x) != valid_s.end()) answer++;

	}
	cout << answer << endl;
}
// limited length of solutions
//so limited recursion