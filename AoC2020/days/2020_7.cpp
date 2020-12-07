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

struct bag {
	string name;
	string color;

	vector<bag> contains;
	vector<int> amounts;
	//map<bag, int, compare_bag> test;
};


regex rule("((\\d+)? ?(\\w+ \\w+)) bag");
smatch sm;

vector<bag> rules;
set<string> answers;

string name_tar = "shiny gold";



bool compare_bag(bag bag1, bag bag2) {
	return bag1.name.compare(bag2.name) == 0;
}

bool compare_color(bag bag1, string tar) {
	return bag1.name.compare(tar) == 0;
}

void print_bag(bag b) {
	cout << b.name;
	if (b.contains.size() > 0) {
		cout << " contains ";
		for (bag p : b.contains) {
			print_bag(p);
			cout << ", ";
		}
	}
}

bag get_bag(string name) {
	for (bag b : rules)
		if (b.name == name)
			return b;
}

bool find_bag(vector<bag> bags, string tar) {
	for (bag sub_bag : bags) {
		if (compare_color(sub_bag, tar)) return true;
	}
	return false;
}

void resursive_search(string name) {
	for (bag b : rules) {
		if (find_bag(b.contains, name)) {
			answers.insert(b.name);
			if (answers.find(b.name) != answers.end())
				resursive_search(b.name);
		}
	}
}

int part2_search(string name) {
	int temp = 0;
	bag curr_bag;

	for (bag b : rules) {
		if (b.name == name)
			curr_bag = b;
	}

	int part2 = 0;
	for (int i = 0; i < curr_bag.contains.size(); i++) {
		bag b = curr_bag.contains[i];
		int amount = curr_bag.amounts[i];

		temp += curr_bag.amounts[i] * part2_search(b.name);

		print_bag(b); cout << temp << endl;

	}
	return 1 + temp;
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_7.txt");

	string x;
	string adjective;
	string color;
	bag curr_bag;

	if (input.is_open()) {
		while (getline(input, x)) {
			regex_search(x, sm, rule);


			curr_bag.name = sm[3];
			x = sm.suffix();


			while (regex_search(x, sm, rule))
			{
				if (sm[3] == "no other") break;
				bag temp;
				temp.name = sm[3];
				curr_bag.contains.push_back(temp);
				curr_bag.amounts.push_back(stoi(sm[2]));
				x = sm.suffix();
			}


			rules.push_back(curr_bag);
			curr_bag = bag();
		}
	}



	int i = 0;
	for (bag b : rules) {
		cout << ++i << endl;

		if (find_bag(b.contains, name_tar)) {

			answers.insert(b.name);
			if (answers.find(b.name) != answers.end())
				resursive_search(b.name);

		}
	}
	cout << "Part 1: " << answers.size() << endl;
	


	cout << part2_search(name_tar) - 1 << endl;
}