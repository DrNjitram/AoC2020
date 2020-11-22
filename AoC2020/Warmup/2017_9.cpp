// AoC2020.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

int calculate_score(string input) {
	// { new group, push to stack, level up one
	 // } close last opened group, level down one
	 // , seperates groups on same level
	 // < opens garbage, then ignore any character that is not >
	 // > closes garbage
	 // ! ignore next character
	string filtered_string = "";

	//cout << "Start: " << input << endl;

	//remove ignored chars
	bool done_removing_exclamation = false;

	while (!done_removing_exclamation) {
		for (int i = 0; i < input.size(); i++) {
			if (input[i] == '!') {
				i++;
			}
			else {
				filtered_string += input[i];
			}
		}

		done_removing_exclamation = count(filtered_string.begin(), filtered_string.end(), '!') == 0;

		if (!done_removing_exclamation) {
			input = filtered_string;
			filtered_string = "";
		}
	}

	//cout << "Removed !: " << filtered_string << endl;


	//remove garbage
	input = filtered_string;
	filtered_string = "";

	int garbage = 0;

	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '<') {
			while (input[i] != '>') {
				i++;
				garbage++;
			}
			garbage--;
		}
		else {
			filtered_string += input[i];
		}
	}

	//cout << "Removed garbage: " << filtered_string << endl;


	//remove empty groups
	input = filtered_string;
	filtered_string = "";


	for (int i = 0; i < input.size(); i++) {
		if (input[i] == ',') {
			while (input[i] == ',')
				i++;
			if (input[i--] != '}')
				filtered_string += ",";
		}
		else {
			filtered_string += input[i];
		}
	}

	//cout << "Removed ,: " << filtered_string << endl;

	input = filtered_string;

	int level = 0;
	int score = 0;


	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '{') {
			level++;
		}
		else if (input[i] == '}') {
			score += level;
			level--;
		}
	}

	cout << score << endl;
	return garbage;
}

int main() {
	cout << "2017 9" << endl;

	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\Warmup\\input\\day9_2017.txt");

	stringstream buffer;
	buffer << input.rdbuf();

	cout << "Removed garbage:" << calculate_score(buffer.str()) << endl;;

	/*
	calculate_score("{}");
	calculate_score("{{{}}}");
	calculate_score("{{},{}}");
	calculate_score("{{{},{},{{}}}}");
	calculate_score("{<a>,<a>,<a>,<a>}");
	calculate_score("{{<ab>},{<ab>},{<ab>},{<ab>}}");
	calculate_score("{{<!!>},{<!!>},{<!!>},{<!!>}}");
	calculate_score("{{<a!>},{<a!>},{<a!>},{<ab>}}");
	*/

}

