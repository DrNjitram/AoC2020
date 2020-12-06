#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;

int intersect_mania(vector<set<char>> sets) {
	set<char> result = sets[0];

	for (set<char> curr_set : sets) {
		set<char> temp;
		set_intersection(result.begin(), result.end(), curr_set.begin(), curr_set.end(), inserter(temp, temp.begin()));
		result = temp;
	}

	return result.size();
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_6.txt");

	string x;
	set<char> answers;
	vector<set<char>> group_answers;

	int score = 0;
	int score2 = 0;

	if (input.is_open()) {
		while (getline(input, x)) {
			if (x == "") {
				score2 += intersect_mania(group_answers);
				score += answers.size();

				answers.clear();
				group_answers.clear();
			}
			else {
				set<char> temp;
				for (char& c : x) {
					answers.insert(c);
					temp.insert(c);
				}
				group_answers.push_back(temp);
			}
		}
	}
	cout << score << endl;
	cout << score2 << endl;
}