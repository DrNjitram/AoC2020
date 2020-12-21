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
#include <array>

using namespace std;

struct Recipe {
	set<string> ing;
	set<string> all;
};

vector<Recipe> cookbook;

set<string> allergens;
set<string> foods;

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\Advent Of Code\\AoC2020\\AoC2020\\input\\2020_21.txt");

	string x;
	while (getline(input, x)) {
		istringstream is(x);

		string s;

		Recipe recipe;

		while (is >> s) {
			if (s.compare("(contains") == 0) {

				while (is >> s) {
					string allergen = s.substr(0, s.length() - 1);

					recipe.all.insert(allergen);
					allergens.insert(allergen);

					if (s[s.length() - 1] == ')') 
						break; 				
				}
				cookbook.push_back(recipe);
				recipe = Recipe();
				break;
			}
			else {
				recipe.ing.insert(s);
				foods.insert(s);
			}

		}
	}

	auto start = chrono::high_resolution_clock::now();

	map<string, string> combinations; // food - allergen
	map<string, string> reverse_combinations;

	for (string food : foods) {
		combinations[food] = "";
	}

	for (string allergy : allergens) {
		reverse_combinations[allergy] = "";
	}

	bool done = false;
	while (!done) {
		for (string allergy : allergens) {
			vector<set<string>> relevant;

			for (Recipe r : cookbook) {
				if (r.all.find(allergy) != r.all.end()) relevant.push_back(r.ing);
			}

			if (relevant.size() < 2) {
				if (relevant.size() == 1) {
					if (relevant[0].size() == 1) {
						string food = *relevant[0].begin();
						//cout << food << ": " << allergy << endl;

						combinations[food] = allergy;
						reverse_combinations[allergy] = food;

						for (Recipe& r : cookbook) {
							r.ing.erase(food);
							r.all.erase(allergy);
						}
					}
				}

			}
			else {

				set<string> intersection;
				set_intersection(relevant[0].begin(), relevant[0].end(), relevant[1].begin(), relevant[1].end(), inserter(intersection, intersection.begin()));

				if (relevant.size() > 2) {
					for (int i = 2; i < relevant.size(); i++) {
						set<string> intermediate_result;
						set_intersection(intersection.begin(), intersection.end(), relevant[i].begin(), relevant[i].end(), inserter(intermediate_result, intermediate_result.begin()));
						intersection = intermediate_result;
					}
				}

				if (intersection.size() == 1) {
					string food = *intersection.begin();
					//cout << food << ": " << allergy << endl;

					combinations[food] = allergy;
					reverse_combinations[allergy] = food;

					for (Recipe& r : cookbook) {
						r.ing.erase(food);
						r.all.erase(allergy);
					}
				}
			}
		}
		
		done = true;
		for (pair<string, string> p : reverse_combinations) {
			if (p.second.compare("") == 0) { done = false; break; }
		}

	}

	int answer = 0;
	for (Recipe r : cookbook) {
		answer += r.ing.size();
	}

	vector<string> sorted_allergy;

	for (string s : allergens) {
		sorted_allergy.push_back(s);
	}

	sort(sorted_allergy.begin(), sorted_allergy.end());

	string answer2 = "";
	for (string allergy : sorted_allergy) {
		answer2 += reverse_combinations[allergy] + ",";
	}

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << answer << endl;
	cout << answer2.substr(0, answer2.length()-1) << endl;
	cout << "Time(us): " << duration.count() << endl;
}
