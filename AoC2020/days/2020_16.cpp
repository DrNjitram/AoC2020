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

regex rule("(?:\\w+ ?)*: (\\d+)-(\\d+) or (\\d+)-(\\d+)");
vector<pair<pair<int, int>, pair<int, int>>> checks;

int arr[20][236];

bool verify(int x) {
	for (pair<pair<int, int>, pair<int, int>> check : checks) 
		if ((x >= check.first.first && x <= check.first.second)|| (x >= check.second.first && x <= check.second.second)) return true;
	
	return false;
}

int main() {
	ifstream input1("C:\\Users\\Martijn\\Desktop\\Advent Of Code\\AoC2020\\AoC2020\\input\\2020_16_1.txt");
	ifstream input2("C:\\Users\\Martijn\\Desktop\\Advent Of Code\\AoC2020\\AoC2020\\input\\2020_16_2.txt");
	ifstream input3("C:\\Users\\Martijn\\Desktop\\Advent Of Code\\AoC2020\\AoC2020\\input\\2020_16_3.txt");

	string x;
	int n;
	int index = 0;
	int answer = 0;
	int row = 1;
	int col = 0;
	smatch sm;

	auto start = chrono::high_resolution_clock::now();

	while (getline(input1, x)) {	
		regex_match(x, sm, rule);
		checks.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(stoi(sm[1]), stoi(sm[2])), pair<int, int>(stoi(sm[3]), stoi(sm[4]))));
	}

	while (input2 >> n)
		arr[index++][0] = n;
	
	while (getline(input3, x)) {

		istringstream is(x);
		vector<int> vals;
		bool invalid = false;
		while (is >> n) {

			if (!verify(n)) {
				answer += n;
				invalid = true;
			}
		}

		if (!invalid) {
			istringstream is2(x);

			while (is2 >> n) 
				arr[col++][row] = n;
							
			row++;
			col = 0;
		}
	}

	map<int, set<int>> fields;

	for (int i = 0; i < checks.size(); i++) {

		set<int> poss;
		for (int j = 0; j < checks.size(); j++) {
			
			pair<pair<int, int>, pair<int, int>> check = checks[j];
			poss.insert(j);

			for (int r = 0; r < row; r++) {
				int v = arr[i][r];

				if (v < check.first.first ||
					(v > check.first.second && v < check.second.first) ||
					v > check.second.second) {
					poss.erase(j);				
					break;
				}
			}
		}
		fields[i] = poss;
	}

	vector<int> done(checks.size());

	bool finished = false;

	while(!finished) {
		finished = true;
		for (int i = 0; i < checks.size(); i++) {
			set<int> s = fields[i];
			if (s.size() == 0) continue;

			if (s.size() == 1) {
				finished = false;
				done[*s.begin()] = i;

				for (int j = 0; j < checks.size(); j++) 
					fields[j].erase(*s.begin());
				
			}
		}
	}

	unsigned long long answer2 = 1;
	for (int i = 0; i < 6; i++) answer2 *= arr[done[i]][0];
	
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << "Part 1: " << answer << endl;
	cout << "Part 2: " << answer2 << endl;

	cout << "Time(us): " << duration.count() << endl;
}