#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <set>
#include <iterator>


using namespace std;


int find_containment(vector<set<int>> sets, int value) {
	int counter = 0;
	for (set<int>& set1 : sets) {
		for (const int& val : set1)
			if (val == value) 
				return counter;
			
		counter++;
	}
	return -1;
}


void merge_sets(vector<set<int>> sets) {
	vector<set<int>> temp;
	for (set<int>& s1 : sets) {
		bool found_intersection = false;

		for (set<int>& s2 : sets) {
			set<int> intersect;
			set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
				inserter(intersect, intersect.begin()));
		}
	}

}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\Warmup\\input\\day12_2017.txt");
	string x;

	regex rule("(\\d+) <-> (\\d+)(?:(?:, (\\d+))*, (\\d+))?");

	vector<set<int>> sets;
	
	set<int> intial_connections;
	intial_connections.insert(0);

	sets.push_back(intial_connections);

	set<int>::iterator it;

	int i = 0;

	if (input.is_open()) {
		while (getline(input, x)) {
			cout << i++ << endl;

			smatch sm;
			regex_match(x, sm, rule);


			bool insert = false;

			set<int> indices;
		
			for (int i = 1; i < sm.size(); i++) {
				if (sm[i] != "") {
					int index = find_containment(sets, stoi(sm[i]));

					if (index != -1) {
						insert = true;
						indices.insert(index);
					}	
				}
			} 


			if (insert) {
				for (int i = 1; i < sm.size(); i++) {
					if (sm[i] != "") {
						sets[*indices.begin()].insert(stoi(sm[i]));
					}
				}
			}
			else {
				set<int> temp;
				for (int i = 1; i < sm.size(); i++) {
					if (sm[i] != "") {
						temp.insert(stoi(sm[i]));
					}
				}
				sets.push_back(temp);
			}

		}

		int counter = 0;
		for (set<int>& set : sets) {
			cout << counter << ": ";
			for (const int& val : set) {
				cout << val << ", ";
			}
			cout << endl;
			counter++;
		}

		cout << sets[0].size() << endl;
	}
}