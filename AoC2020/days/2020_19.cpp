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
		//cout << x << endl;

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
	
	auto start = chrono::high_resolution_clock::now();

	vector<string> bit1 = rule_search(42);
	vector<string> bit2 = rule_search(31);

	set<string> b1_s;
	size_t size_b1 = bit1[0].length();
	for (string s : bit1) b1_s.insert(s);

	set<string> b2_s;
	size_t size_b2 = bit2[0].length();
	for (string s : bit2) b2_s.insert(s);

	int answer = 0;
	int answer2 = 0;
	while (getline(input, x)) {
		if (b1_s.find(x.substr(0, size_b1)) != b1_s.end()) {
			if (b1_s.find(x.substr(size_b1, size_b1)) != b1_s.end()) {
				if (b2_s.find(x.substr(size_b1 * 2, x.length())) != b2_s.end()) answer++;
			}
		}
		else {
			continue;
		}

		int no_1 = 0;
		while (true) {
			if (b2_s.find(x.substr(x.length() - size_b2, size_b2)) != b2_s.end()) {
				no_1++;
				x = x.substr(0, x.length() - size_b2);
			}
			else {
				break;
			}

		}
		if (no_1 == 0) continue;

		int no_2 = 0;
		while (true) {
			if (b1_s.find(x.substr(x.length() - size_b1, size_b1)) != b1_s.end()) {
				no_2++;

				if (x.length() == size_b1) break;
				x = x.substr(0, x.length() - size_b1);
				
			}
			else {
				break;
			}

		}
		if (no_2 - no_1 > 0) answer2++;
	}



	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << answer << endl;
	cout << answer2 - 1<< endl;
	cout << "Time(us): " << duration.count() << endl;
}
